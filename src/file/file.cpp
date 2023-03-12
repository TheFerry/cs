#include "file.h"
#include "../assets/icons.h"
#include "../core/arranger.h"
#include "../core/flags.h"
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <ostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
file::Dir::Dir(std::string directory) {
  auto &iconInfo = icon::IconInfo;
  auto &iconSet = icon::IncoSet;
  namespace fs = std::filesystem;
  uint32_t flags = core::Flags::getInstance().getFlag(); // 获取程序解析参数
  this->info.name = ".";

  fs::path pa(directory);
  fs::file_status status = fs::status(pa);
  // 填充当前目录的信息
  //  this->info.size = fs::file_size(pa);
  this->info.modTime = fs::last_write_time(pa);
  if (!(flags & core::Flags::flag_i)) {
    this->info.icon = iconInfo.at("diropen").getGraph();
    this->info.iconColor = iconInfo.at("diropen").getColor();
  }

  // 获取目录中所有文件信息
  for (auto &entry : fs::directory_iterator(pa)) {
    FileInfo file;
    file.name = entry.path();
    if(file.name != "."&&file.name!=".."){
      file.name = file.name.substr(2, file.name.size() - 2);
    }
    if(!(flags&core::Flags::flag_a)){
      if(file.name[0] == '.'){
        continue;
      }
    }
    if (!fs::is_directory(entry)) {
      file.extension = entry.path().extension();
      if (file.extension.size() > 0) {
        file.extension = file.extension.substr(1, file.extension.size() - 1);
      }
      file.size = entry.file_size();
      if (file.extension.size() > 0) {
        file.icon = iconSet.at(file.extension).getGraph();
        file.iconColor = iconSet.at(file.extension).getColor();
      }
    } else {
      file.icon = iconInfo.at("dir").getGraph();
      file.iconColor = iconInfo.at("dir").getColor();
    }
    file.modTime = entry.last_write_time();
    this->files.push_back(file);
    if (fs::is_directory(entry)) {
      this->dirs.push_back(file.name + "/");
    }
  }
  if (flags & core::Flags::flag_a) {
    this->files.push_back(this->info);
    this->parent.name = "..";
 //   this->parent.size = fs::file_size(parent);
    this->parent.modTime = fs::last_write_time(this->parent.name);
    if (!(flags & core::Flags::flag_i)) {
      this->parent.icon = iconInfo.at("dir").getGraph();
      this->parent.iconColor = iconInfo.at("dir").getColor();
    }
    this->files.push_back(this->parent);
  }
}

std::vector<uint8_t> file::Dir::print() {
  std::vector<uint8_t> buf;
  struct winsize size;
  ioctl(stdin->_fileno, TIOCGWINSZ, &size);
  core::arranger arranger(size.ws_col);
  for (const auto &v : this->files) {
    arranger.addRow({"", v.icon, v.name});
    arranger.iconColor(v.iconColor);
  }
  arranger.flush(buf);
  return buf;
}
