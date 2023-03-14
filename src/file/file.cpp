#include "file.h"
#include "../assets/iconDirs.h"
#include "../assets/iconExtension.h"
#include "../assets/iconFilename.h"

#include "../core/arranger.h"
#include "../core/flags.h"
#include "../core/logger.h"
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <ostream>
#include <string>
#ifdef __linux__
#include <sys/ioctl.h>
#endif
#ifdef _WIN32
#include <Windows.h>
#endif
#include <tuple>

std::string file::Dir::getIncidator(const FileInfo& info) const {
  namespace fs = std::filesystem;
  if (info.isDir) { // 是一个目录
    return "/";
  }
  if (info.fileType == fs::file_type::fifo) { // 是一个管道
    return "|";
  }
  if (info.fileType == fs::file_type::symlink) { // 是一个链接
    return "@";
  }
  if (info.fileType == fs::file_type::socket) { // 是一个socket
    return "=";
  }
  if ((info.modeBits & fs::perms::owner_exec) != fs::perms::none) { // 可执行文件
    return "*";
  }
  return "";
}

std::pair<std::string, std::string>
file::Dir::getIcon(const std::string &name, const std::string &extension,
                   const std::string &indicator) {
  // 默认当前目录和父目录是没有加indicator的
  if (name == "." || name == "..") {
    auto i = icon::iconInfo.at("diropen");
    return {i.getGraph(), i.getColor()};
  }
  std::string lname;
  std::string lext;
  lname.resize(name.size());
  lext.resize(extension.size());
  auto lam = [](char a) { return static_cast<char>(std::tolower(a)); };

  std::transform(extension.begin(), extension.end(), lext.begin(), lam);
  std::transform(name.begin(), name.end(), lname.begin(), lam);

  if (indicator == "/") { // 如果是目录
    auto it = icon::iconDirs.find(lname);
    // 查询是否为特殊目录
    if (it != icon::iconDirs.end()) {
      return {it->second.getGraph(), it->second.getColor()};
    }
    // 是否为隐藏目录
    if (name[0] == '.') {
      auto i = icon::iconInfo.at("hiddendir");
      return {i.getGraph(), i.getColor()};
    }
    // 普通目录
    auto i = icon::iconInfo.at("dir");
    return {i.getGraph(), i.getColor()};
  }
  // 查找是否为特殊文件名
  auto itn = icon::iconFilename.find(lname);
  if (itn != icon::iconFilename.end()) {
    return {itn->second.getGraph(), itn->second.getColor()};
  }
  // 查找文件扩展名
  auto ite = icon::iconExtension.find(lext);
  if (ite != icon::iconExtension.end()) {
    return {ite->second.getGraph(), ite->second.getColor()};
  }
  // 是否为隐藏文件
  if (name[0] == '.') {
    auto i = icon::iconInfo.at("hiddenfile");
    return {i.getGraph(), i.getColor()};
  }
  // 其他文件
  auto i = icon::iconInfo.at("file");

  // 是否为可执行文件
  if (indicator == "*") {
    i = icon::iconInfo.at("exe");
    i.toExe();
  }
  return {i.getGraph(), i.getColor()};
}

size_t file::Dir::getSize(const std::filesystem::path &path) const {
  namespace fs = std::filesystem;
  // 暂时先不获取文件夹的大小
  if (fs::is_directory(path)) {
    return 4096;
  }
  return fs::file_size(path);
}

file::Dir::Dir(std::string directory) {
  auto &iconInfo = icon::iconInfo;
  auto &iconSet = icon::iconSet;
  namespace fs = std::filesystem;
  uint32_t flags = core::Flags::getInstance().getFlag(); // 获取程序解析参数
  info.name = ".";
  info.isDir = true;
  fs::path pa(directory);
  auto status= fs::status(pa);
  info.fileType = status.type();
  info.modeBits  = status.permissions();
  // 填充当前目录的信息
  info.size = getSize(pa);
  info.modTime = fs::last_write_time(pa);
  if (!(flags & core::Flags::flag_i)) {
    std::tie(info.icon, info.iconColor) =
        getIcon(info.name, info.extension, info.indicator);
  }

  // 获取目录中所有文件信息
  for (auto &entry : fs::directory_iterator(pa)) {
    bool isDir = fs::is_directory(entry);
    FileInfo file;
    auto status= fs::status(entry);
    file.fileType = status.type();
    file.modeBits  = status.permissions();
    file.isDir = isDir;
    file.name = entry.path().string();
    file.name = file.name.substr(2, file.name.size() - 2);
    if (!(flags & core::Flags::flag_a)) {
      if (file.name[0] == '.') { // 跳过隐藏目录
        continue;
      }
    }

    file.extension = entry.path().extension().string();
    if (file.extension.size() > 0) {
      file.extension = file.extension.substr(1, file.extension.size() - 1);
    }
    file.size = getSize(entry);
    file.modTime = entry.last_write_time();
    file.indicator = getIncidator(file);
    // 获取图标信息，带有-i参数时不显示图标
    if (!(flags & core::Flags::flag_i)) {
      std::tie(file.icon, file.iconColor) =
          getIcon(file.name, file.extension, file.indicator);
    }
    files.push_back(file);
    if (isDir) {
      dirs.push_back(file.name);
    }
  }
  // 带有 -a参数
  if (flags & core::Flags::flag_a) {
    files.push_back(info); // 添加自身
    // 添加父目录
    parent.name = "..";
    parent.isDir = true;

    auto status= fs::status(parent.name);
    parent.fileType = status.type();
    parent.modeBits  = status.permissions();

    parent.size = getSize(parent.name);
    parent.modTime = fs::last_write_time(parent.name);
    if (!(flags & core::Flags::flag_i)) {
      std::tie(parent.icon, parent.iconColor) =
          getIcon(parent.name, parent.extension, parent.indicator);
    }
    files.push_back(parent);
  }
  std::sort(files.begin(), files.end(),
            [](FileInfo &a, FileInfo &b) {
              auto as = a.name;
              auto bs = b.name;
              if (as[0] == '.') {
                as = as.substr(1, as.size() - 1);
              }
              if (bs[0] == '.') {
                bs = bs.substr(1, bs.size() - 1);
              }
              auto func = [](char c) { return std::tolower(c); };
              std::transform(as.begin(), as.end(), as.begin(), func);
              std::transform(bs.begin(), bs.end(), bs.begin(), func);
              return as < bs;
            });
}

std::vector<uint8_t> file::Dir::print() {
  std::vector<uint8_t> buf;
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

  core::arranger arranger(termWidth);
  for (const auto &v : files) {
    arranger.addRow({"", v.icon, v.name + v.indicator});
    arranger.iconColor(v.iconColor);
  }
  arranger.flush(buf);
  return buf;
}
