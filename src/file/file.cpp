#include "file.h"
#include "arranger.h"
#include "iconDirs.h"
#include "iconExtension.h"
#include "iconFilename.h"
#include "longArranger.h"
#include "term.h"

#include <cmath>
#include <dirent.h>
#include <grp.h>
#include <limits.h>
#include <pwd.h>
#include <string>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

// 装载文件按全部权限的字符串
void file::Dir::getMode(file::FileInfo &info) {
  // 获取文件信息
  struct stat fileStat;
  std::string permissions;
  if (lstat(info.path.c_str(), &fileStat) == 0) {
    // 获取文件权限
    permissions += (info.isDir) ? "d" : "-";
    if (S_ISLNK(fileStat.st_mode)) {
      permissions[0] = 'l';
    }
    permissions += (fileStat.st_mode & S_IRUSR) ? "r" : "-";
    permissions += (fileStat.st_mode & S_IWUSR) ? "w" : "-";
    permissions += (fileStat.st_mode & S_IXUSR) ? "x" : "-";
    permissions += (fileStat.st_mode & S_IRGRP) ? "r" : "-";
    permissions += (fileStat.st_mode & S_IWGRP) ? "w" : "-";
    permissions += (fileStat.st_mode & S_IXGRP) ? "x" : "-";
    permissions += (fileStat.st_mode & S_IROTH) ? "r" : "-";
    permissions += (fileStat.st_mode & S_IWOTH) ? "w" : "-";
    permissions += (fileStat.st_mode & S_IXOTH) ? "x" : "-";
  } else {
    permissions = "ERR";
    info.broken = true;
  }
  info.mode = std::move(permissions);
}

// 根据文件类型获取后缀
void file::Dir::getIncidator(FileInfo &info) const {
  // 获取文件信息
  struct stat fileStat;
  std::string indicator = "";
  if (lstat(info.path.c_str(), &fileStat) == 0) {
    // 判断文件类型
    if (S_ISREG(fileStat.st_mode) &&
        (fileStat.st_mode & S_IXUSR || fileStat.st_mode & S_IXGRP ||
         fileStat.st_mode & S_IXOTH)) {
      indicator = "*";
    }
    if (S_ISDIR(fileStat.st_mode)) {
      indicator = "/";
    }
    if (S_ISFIFO(fileStat.st_mode)) {
      indicator = "|";
    }
    if (S_ISSOCK(fileStat.st_mode)) {
      indicator = "=";
    }
    if (S_ISCHR(fileStat.st_mode) || S_ISBLK(fileStat.st_mode)) {
    }
    if (S_ISLNK(fileStat.st_mode)) {
      indicator = "@";
    }
    info.indicator = indicator;
  }
}

// 获取目标链接
void file::Dir::getLinkTarget(FileInfo &info) {
  if (info.indicator == "@") {
    char targetPath[1024]; // 存储目标文件路径的缓冲区
    // 调用 readlink() 函数获取链接文件的目标文件路径
    ssize_t result =
        readlink(info.path.c_str(), targetPath, sizeof(targetPath) - 1);
    if (result != -1) {
      targetPath[result] = '\0'; // 添加字符串结束符
      info.targetLink = new FileInfo;
      info.targetLink->path = targetPath;
      if (targetPath[0] != '/') {
        // 如果目标路径是相对路径，则将其转换为绝对路径
        char absTargetPath[PATH_MAX];
        std::string basepath = core::Flags::getInstance().path();
        if (basepath[basepath.size() - 1] != '/') {
          basepath += '/';
        }
        basepath += targetPath;
        if (realpath(basepath.c_str(), absTargetPath) != nullptr) {
          info.targetLink->name = targetPath;
          info.targetLink->path = absTargetPath;
        }
      }
    } else {
      info.broken = true;
    }
  }
}

// 获取图标信息
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

// 获取文件大小
void file::Dir::getSize(file::FileInfo &info) {
  struct stat filestat;
  const char units[] = {'B', 'K', 'M', 'G', 'T', 'P', 'E', 'Z', 'Y'};
  const int base = 1024;
  if (info.isDir) {
    info.size = "4.0K";
    return;
  }
  uintmax_t realsize = 0;
  if (lstat(info.path.c_str(), &filestat) == 0) {
    realsize = filestat.st_size;
  } else {
    info.size = "0";
    info.broken = true;
    return;
  }
  if(realsize == 0){
    info.size = "0";
    return;
  }
  int unitIndex = std::floor(std::log(realsize) / std::log(base));
  double size = static_cast<double>(realsize) / std::pow(base, unitIndex);
  int afterdot = size - static_cast<uintmax_t>(size) < 0.1 ? 0 : 1;
  char sizebuf[20];
  sprintf(sizebuf, "%.*f%c", afterdot, size, units[unitIndex]);
  info.size = sizebuf;
}

// 获取时间信息
void file::Dir::getTimeString(FileInfo &info) {
  struct stat fileStat; // 存储文件信息的结构体
  // 获取文件信息
  if (stat(info.path.c_str(), &fileStat) == 0) {
    // 获取文件的修改时间
    time_t modifiedTime = fileStat.st_mtime;
    struct tm *tmTime = localtime(&modifiedTime);
    char timeBuffer[100];
    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M", tmTime);
    info.modtimeString = std::string(timeBuffer);
  } else {
    info.modtimeString = "ERR";
    info.broken = true;
  }
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
  if (stat(info.path.c_str(), &info.filestat) != 0) {
    return false;
  };
  info.isDir = S_ISDIR(info.filestat.st_mode);
  lstat(info.path.c_str(), &info.filestat);
  auto flags = core::Flags::getInstance().getFlag();
  if (flags & core::Flags::flag_d) { // 只列出目录
    if (!info.isDir)
      return false;
  }
  auto getFileName = [](const std::string &filePath) {
    // 找到最后一个斜杠字符的位置
    size_t lastSlashPos = filePath.find_last_of("/\\");

    // 提取文件名
    std::string fileName = filePath.substr(lastSlashPos + 1);

    return fileName;
  };

  auto getFileExtension = [](const std::string &filePath) {
    // 找到最后一个点字符的位置
    int lastDotPos = filePath.find_last_of('.');
    if (lastDotPos == -1) {
      return std::string("");
    }
    // 提取扩展名
    std::string fileExtension = filePath.substr(lastDotPos + 1);
    return fileExtension;
  };
  info.name = getFileName(info.path);
  info.extension = getFileExtension(info.name);
  if (!(flags & core::Flags::flag_a || flags & core::Flags::flag_A)) {
    if (info.name[0] == '.') { // 跳过隐藏目录
      return false;
    }
  }
  getIncidator(info);
  getSize(info);
  getOwnerAndGroup(info);
  if (flags & core::Flags::flag_l) {
    getLinkTarget(info); // 为链接也添加信息
  }
  getTimeString(info);
  // 获取图标信息，带有-i参数时不显示图标
  if (!(flags & core::Flags::flag_i)) {
    std::tie(info.icon, info.iconColor) = getIcon(info);
  }
  getMode(info);
  // 修改路径名称，对于链接文件而言，简化输出,其他文件用不上
  /* info.path = fs::path(info.path).lexically_proximate( */
  /*     core::Flags::getInstance().path()); */
  return true;
}

file::Dir::Dir(std::string directory) {
  auto &iconInfo = icon::iconInfo;
  auto &iconSet = icon::iconSet;
  // 先解决链接的文件夹
  info = new FileInfo;
  const char *repath = directory.c_str();
  lstat(directory.c_str(), &info->filestat);
  char absTargetPath[PATH_MAX];
  if (S_ISLNK(info->filestat.st_mode)) {
    // 如果目标路径是相对路径，则将其转换为绝对路径
    std::string basepath = core::Flags::getInstance().path();
    if (basepath[basepath.size() - 1] != '/') {
      basepath += '/';
    }
    realpath(basepath.c_str(), absTargetPath);
    repath = absTargetPath;
  }
  DIR *dir = opendir(repath);
  if (dir == nullptr) {
    throw DirException("Failed to open directory: " + std::string(repath));
    return;
  }

  uint32_t flags = core::Flags::getInstance().getFlag(); // 获取程序解析参数
  struct dirent *entry;
  while ((entry = readdir(dir)) != nullptr) {
    std::string entryName = entry->d_name;
    std::string entryPath = directory + "/" + entryName;
    FileInfo *file = new FileInfo;
    file->path = entryPath;
    if (encapsulationFileInfo(*file)) {
      // 如果目标是一个链接，还要对其实际文件进行装箱
      if (flags & core::Flags::flag_l && file->indicator == "@" &&
          file->targetLink) {
        encapsulationFileInfo(*file->targetLink);
        file->icon = file->targetLink->icon;
        file->iconColor = file->targetLink->iconColor;
      }
      files.push_back(file);
    } else
      delete file;
  }
  closedir(dir);
  info->isDir = true;
  // 填充指定目录的信息
  info->path = directory;
  info->name = ".";
  info->isDir = true;
  getTimeString(*info);
  getOwnerAndGroup(*info);
  getSize(*info);
  getMode(*info);
  if (!(flags & core::Flags::flag_i)) {
    std::tie(info->icon, info->iconColor) = getIcon(*info);
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
  winsize size;
  ioctl(stdin->_fileno, TIOCGWINSZ, &size);
  termWidth = size.ws_col;
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

/* file::dir::~dir() { */
/*   for (auto it = files.begin(); it != files.end(); ++it) { */
/*     if (*it == info || *it == parent) { */
/*       continue; */
/*     } */
/*     delete *it; */
/*   } */
/*   files.clear(); */
/*   delete info; */
/*   delete parent; */
/* } */
