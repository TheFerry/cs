#include "file.h"
#include "arranger.h"
#include "flags.h"
#include "iconDirs.h"
#include "iconExtension.h"
#include "iconFilename.h"
#include "icons.h"
#include "logger.h"
#include "longArranger.h"
#include "term.h"

#include <algorithm>
#include <chrono>
#include <ctime>
#include <exception>
#include <filesystem>
#include <grp.h>
#include <iostream>
#include <pwd.h>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <system_error>

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
  if (fs::symlink_status(info.path).type() ==
      fs::file_type::symlink) { // 是一个链接
    info.indicator = "@";
  } else if (info.fileType == fs::file_type::fifo) { // 是一个管道
    info.indicator = "|";
  } else if (info.isDir) { // 是一个目录
    info.indicator = "/";
  } else if (info.fileType == fs::file_type::socket) { // 是一个socket
    info.indicator = "=";
  } else if ((info.permission & fs::perms::owner_exec) !=
             fs::perms::none) { // 可执行文件
    info.indicator = "*";
  } else {
    info.indicator = "";
  }
}

void file::Dir::getLinkTargeet(FileInfo &info) {
  if (info.indicator == "@") {
    std::string targetlink =
        std::filesystem::read_symlink(std::filesystem::path(info.path));
    info.targetLink = new FileInfo; // 0,191,255
    info.targetLink->path = targetlink;
  }
}
std::pair<std::string, std::string>
file::Dir::getIcon(const file::FileInfo &info) const {
  icon::IconInfo i;
  auto name = info.name;
  auto extension = info.extension;
  auto indicator = info.indicator;
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

  if (info.isDir) { // 如果是目录
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
    if (fs::is_regular_file(info.path))
      size = fs::file_size(info.path);
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
  return {bufferYear.str(), bufferMonth.str(), bufferDay.str(),
          bufferTime.str()};
}

void file::Dir::getOwnerAndGroup(FileInfo &info) {
  struct stat buf;
  if (stat(info.path.c_str(), &buf) == -1) {
    return;
  }
  struct passwd *pw = getpwuid(buf.st_uid);
  struct group *grp = getgrgid(buf.st_gid);
  info.group = grp ? grp->gr_name : "unkonwn";
  info.owner = pw ? pw->pw_name : "unkonwn";
}

bool file::Dir::encapsulationFileInfo(FileInfo &info) {
  namespace fs = std::filesystem;
  auto entry = fs::path(info.path);
  auto flags = core::Flags::getInstance().getFlag();
  bool isDir = fs::is_directory(entry);
  if (flags & core::Flags::flag_d) { // 只列出目录
    if (!isDir)
      return false;
  }
  auto status = fs::status(entry);
  info.fileType = status.type();
  info.permission = status.permissions();
  info.isDir = isDir;
  info.name = entry;
  info.extension = entry.extension().string();

  int idx1 = info.name.rfind('/') + 1;
  if (idx1 != -1) {
    info.name = info.name.substr(idx1, info.name.size() - idx1);
  } else {
    info.name = info.name.substr(2, info.name.size() - 2);
  }
  if (!(flags & core::Flags::flag_a || flags & core::Flags::flag_A)) {
    if (info.name[0] == '.') { // 跳过隐藏目录
      return false;
    }
  }
  if (info.extension.size() > 0) {
    info.extension = info.extension.substr(1, info.extension.size() - 1);
  }

  getIncidator(info);
  getSize(info);
  getOwnerAndGroup(info);
  if (flags & core::Flags::flag_l) {
    getLinkTargeet(info); // 为链接也添加信息
  }
  try {
    info.modtimeString = getTimeString(fs::last_write_time(entry));
  } catch (std::filesystem::filesystem_error &e) {
    info.modtimeString = {"ERR", "ERR", "ERR", "ERR"};
    info.broken = true;
  }
  // 获取图标信息，带有-i参数时不显示图标
  if (!(flags & core::Flags::flag_i)) {
    std::tie(info.icon, info.iconColor) = getIcon(info);
  }
  getMode(info);
  return true;
}

file::Dir::Dir(std::string directory) {
  auto &iconInfo = icon::iconInfo;
  auto &iconSet = icon::iconSet;
  namespace fs = std::filesystem;
  if (!fs::is_directory(directory)) {
    throw fs::filesystem_error(
        directory + " is not a directory", directory,
        std::make_error_code(std::errc::no_such_file_or_directory));
  }
  uint32_t flags = core::Flags::getInstance().getFlag(); // 获取程序解析参数
  info = new FileInfo;
  // 填充指定目录的信息
  info->path = directory;
  info->name = ".";
  info->isDir = true;
  info->fileType = fs::file_type::directory;
  info->modtimeString = getTimeString(fs::last_write_time(info->path));
  info->permission = fs::status(info->path).permissions();
  getOwnerAndGroup(*info);
  getSize(*info);
  getMode(*info);
  if (!(flags & core::Flags::flag_i)) {
    std::tie(info->icon, info->iconColor) = getIcon(*info);
  }
  // 修改info名字
  //  获取目录中所有文件信息
  for (auto &entry : fs::is_directory(directory)
                         ? fs::directory_iterator(directory)
                         : fs::directory_iterator(info->name)) {
    FileInfo *file = new FileInfo;
    file->path = entry.path();
    if (encapsulationFileInfo(*file)) {
      // 如果目标是一个链接，还要对其实际文件进行装箱
      if (flags & core::Flags::flag_l && file->indicator == "@") {
        encapsulationFileInfo(*file->targetLink);
      }
      files.push_back(file);
    } else
      delete file;
  }
  // 带有 -a参数
  if (flags & core::Flags::flag_a) {
    files.push_back(info); // 添加自身
    parent = new FileInfo;
    // 添加父目录
    parent->name = "..";
    parent->path = info->path + "/..";
    parent->isDir = true;
    parent->fileType = fs::file_type::directory;
    parent->permission = fs::status(parent->path).permissions();
    getSize(*parent);
    getMode(*parent);
    getOwnerAndGroup(*parent);
    parent->modtimeString = getTimeString(fs::last_write_time(parent->path));
    if (!(flags & core::Flags::flag_i)) {
      std::tie(parent->icon, parent->iconColor) = getIcon(*parent);
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
