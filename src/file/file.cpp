#include "file.h"
#include "arranger.h"
#include "flags.h"
#include "iconDirs.h"
#include "iconExtension.h"
#include "iconFilename.h"
#include "logger.h"
#include "longArranger.h"
#include "term.h"

#include <algorithm>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <grp.h>
#include <iostream>
#include <pwd.h>
#include <string>
#include <sys/stat.h>

#ifdef __linux__
#include <sys/ioctl.h>
#endif

#ifdef _WIN32
#include <Windows.h>
#endif

// 装载文件按全部权限的字符串
void file::Dir::getMode(file::FileInfo &info) {
  std::string perms;
  perms += info.isDir ? "d" : "-";
  perms += (info.permission & std::filesystem::perms::owner_read) !=
                   std::filesystem::perms::none
               ? "r"
               : "-";
  perms += (info.permission & std::filesystem::perms::owner_write) !=
                   std::filesystem::perms::none
               ? "w"
               : "-";
  perms += (info.permission & std::filesystem::perms::owner_exec) !=
                   std::filesystem::perms::none
               ? "x"
               : "-";
  perms += (info.permission & std::filesystem::perms::group_read) !=
                   std::filesystem::perms::none
               ? "r"
               : "-";
  perms += (info.permission & std::filesystem::perms::group_write) !=
                   std::filesystem::perms::none
               ? "w"
               : "-";
  perms += (info.permission & std::filesystem::perms::group_exec) !=
                   std::filesystem::perms::none
               ? "x"
               : "-";
  perms += (info.permission & std::filesystem::perms::others_read) !=
                   std::filesystem::perms::none
               ? "r"
               : "-";
  perms += (info.permission & std::filesystem::perms::others_write) !=
                   std::filesystem::perms::none
               ? "w"
               : "-";
  perms += (info.permission & std::filesystem::perms::others_exec) !=
                   std::filesystem::perms::none
               ? "x"
               : "-";
  info.mode = perms;
}

void file::Dir::getIncidator(FileInfo &info) const {
  namespace fs = std::filesystem;
  if (info.isDir) { // 是一个目录
    info.indicator = "/";
  } else if (info.fileType == fs::file_type::fifo) { // 是一个管道
    info.indicator = "|";
  } else if (fs::symlink_status(info.name).type() ==
             fs::file_type::symlink) { // 是一个链接
    info.indicator = "@";
  } else if (info.fileType == fs::file_type::socket) { // 是一个socket
    info.indicator = "=";
  } else if ((info.permission & fs::perms::owner_exec) !=
             fs::perms::none) { // 可执行文件
    info.indicator = "*";
  } else {
    info.indicator = "";
  }
}

std::pair<std::string, std::string>
file::Dir::getIcon(const std::string &name, const std::string &extension,
                   const std::string &indicator) {
  icon::IconInfo i;
  // 默认当前目录和父目录是没有加indicator的
  if (name == "." || name == "..") {
    i = icon::iconInfo.at("diropen");
    return {i.getGraph(), i.getColor()};
  }
  std::string lname;
  std::string lext;
  lname.resize(name.size());
  lext.resize(extension.size());
  std::transform(extension.begin(), extension.end(), lext.begin(), tolower);
  std::transform(name.begin(), name.end(), lname.begin(), tolower);
  // 查找是否为特殊文件名
  auto itn = icon::iconFilename.find(lname);
  // 查找文件扩展名
  auto ite = icon::iconExtension.find(lext);

  if (indicator == "/") { // 如果是目录
    auto it = icon::iconDirs.find(lname);
    // 普通目录
    i = icon::iconInfo.at("dir");
    // 是否为隐藏目录
    if (name[0] == '.') {
      i = icon::iconInfo.at("hiddendir");
    }
    // 查询是否为特殊目录
    if (it != icon::iconDirs.end()) {
      i = it->second;
    }
  } else if (itn != icon::iconFilename.end()) {
    i = itn->second;
  } else if (ite != icon::iconExtension.end()) {
    i = ite->second;
  } else
    // 是否为隐藏文件
    if (name[0] == '.') {
      i = icon::iconInfo.at("hiddenfile");
    } else {
      // 其他文件
      i = icon::iconInfo.at("file");
    }
  // 是否为可执行文件
  if (indicator == "*") {
    i.toExe();
  }
  return {i.getGraph(), i.getColor()};
}

void file::Dir::getSize(file::FileInfo &info) {
  namespace fs = std::filesystem;
  size_t size = 0;
  // 暂时先不获取文件夹的大小
  if (info.isDir) {
    size = 4096;
  } else {
    if (fs::is_regular_file(info.name))
      size = fs::file_size(info.name);
    else
      size = 0;
  }
  info.size = size;
}

template <typename TP>
std::vector<std::string> file::Dir::getTimeString(TP tp) {
  using namespace std::chrono;
  auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() +
                                                      system_clock::now());
  std::vector<std::string> timeVec(4);
  auto time = system_clock::to_time_t(sctp);
  std::tm *gmt = std::gmtime(&time);
  std::stringstream bufferYear;
  std::stringstream bufferMonth;
  std::stringstream bufferDay;
  std::stringstream bufferTime;
  bufferYear << std::put_time(gmt, "%Y");
  bufferMonth << std::put_time(gmt, "%B");
  bufferDay << std::put_time(gmt, "%d");
  bufferTime << std::put_time(gmt, "%H:%M");
  timeVec[0] = bufferYear.str();
  timeVec[1] = bufferMonth.str();
  timeVec[2] = bufferDay.str();
  timeVec[3] = bufferTime.str();
  return timeVec;
}

void file::Dir::getOwnerAndGroup(FileInfo &info) {
  struct stat buf;
  if (stat(info.name.c_str(), &buf) == -1) {
    return;
  }
  struct passwd *pw = getpwuid(buf.st_uid);
  struct group *grp = getgrgid(buf.st_gid);
  info.group = grp ? grp->gr_name : "unkonwn";
  info.owner = pw ? pw->pw_name : "unkonwn";
}

file::Dir::Dir(std::string directory) {
  parent = new FileInfo;
  info = new FileInfo;
  auto &iconInfo = icon::iconInfo;
  auto &iconSet = icon::iconSet;
  namespace fs = std::filesystem;
  uint32_t flags = core::Flags::getInstance().getFlag(); // 获取程序解析参数

  //填充指定目录的信息
  info->name = directory;
  info->isDir = true;
  getOwnerAndGroup(*info);
  fs::path pa(directory);
  info->fileType = fs::file_type::directory;
  getSize(*info);
  info->modtimeString = getTimeString(fs::last_write_time(pa));
  if (!(flags & core::Flags::flag_i)) {
    info->name = ".";
    std::tie(info->icon, info->iconColor) =
        getIcon(info->name, info->extension, info->indicator);
  }
  info->permission = fs::status(pa).permissions();
  getMode(*info);
  //修改info名字
  // 获取目录中所有文件信息
  for (auto &entry : fs::directory_iterator(directory)) {
    bool isDir = fs::is_directory(entry);
    if (flags & core::Flags::flag_d) { // 只列出目录
      if (!isDir)
        continue;
    }
    FileInfo *file = new FileInfo;
    auto status = entry.status();
    auto path = entry.path();

    file->fileType = status.type();
    file->permission = status.permissions();
    file->isDir = isDir;
    file->name = path.string();
    int idx1 = file->name.rfind('/') + 1;
    if (idx1 != -1) {
      file->name = file->name.substr(idx1, file->name.size() - idx1);
    } else {
      file->name = file->name.substr(2, file->name.size() - 2);
    }
    if (!(flags & core::Flags::flag_a || flags & core::Flags::flag_A)) {
      if (file->name[0] == '.') { // 跳过隐藏目录
        continue;
      }
    }

    file->extension = path.extension().string();
    if (file->extension.size() > 0) {
      file->extension = file->extension.substr(1, file->extension.size() - 1);
    }
    getSize(*file);
    file->modtimeString = getTimeString(entry.last_write_time());
    getIncidator(*file);
    getOwnerAndGroup(*file);
    // 获取图标信息，带有-i参数时不显示图标
    if (!(flags & core::Flags::flag_i)) {
      std::tie(file->icon, file->iconColor) =
          getIcon(file->name, file->extension, file->indicator);
    }
    getMode(*file);
    files.push_back(file);
    if (isDir) {
      dirs.push_back(file->name);
    }
  }
  // 带有 -a参数
  if (flags & core::Flags::flag_a) {
    files.push_back(info); // 添加自身
    // 添加父目录
    parent->name = "..";
    parent->isDir = true;
    parent->fileType = fs::file_type::directory;
    parent->permission = fs::status(parent->name).permissions();
    getSize(*parent);
    getMode(*parent);
    getOwnerAndGroup(*parent);
    parent->modtimeString = getTimeString(fs::last_write_time(parent->name));
    if (!(flags & core::Flags::flag_i)) {
      std::tie(parent->icon, parent->iconColor) =
          getIcon(parent->name, parent->extension, parent->indicator);
    }
    files.push_back(parent);
  }

  std::sort(files.begin(), files.end(),
            [](const FileInfo *a, const FileInfo *b) {
              auto as = a->name;
              auto bs = b->name;
              if (as[0] == '.') {
                as = as.substr(1, as.size() - 1);
              }
              if (bs[0] == '.') {
                bs = bs.substr(1, bs.size() - 1);
              }
              std::transform(as.begin(), as.end(), as.begin(), tolower);
              std::transform(bs.begin(), bs.end(), bs.begin(), tolower);
              return as < bs;
            });
  if (flags & core::Flags::flag_r) {
    std::reverse(files.begin(), files.end());
  }
}

std::string file::Dir::print() {
  std::string buf;
  int termWidth = 80;
#ifdef __linux__
  winsize size;
  ioctl(stdin->_fileno, TIOCGWINSZ, &size);
  termWidth = size.ws_col;
#endif

#ifdef _WIN32
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  termWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
#endif
  core::Term *arranger;
  if (core::Flags::getInstance().getFlag() & core::Flags::flag_l) {
    arranger = new core::LongArranger();
  } else {
    arranger = new core::arranger(termWidth);
  }
  arranger->setData(files);
  arranger->flush(buf);
  delete arranger;
  return buf;
}

file::Dir::~Dir() {
  for (auto it = files.begin(); it != files.end(); ++it) {
    if (*it == info || *it == parent) {
      continue;
    }
    delete *it;
  }
  files.clear();
  delete info;
  delete parent;
}
