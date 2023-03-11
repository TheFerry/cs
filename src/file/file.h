#pragma once
#include <list>
#include <memory>
#include <string>
/// 文件信息
class FileInfo {
private:
  std::string name;      //<文件名
  std::string extension; //<文件拓展名
  size_t size;           //<文件大小
  std::string mode;      //<文件权限
  uint32_t modeBits;
  std::string owner;     //<文件所有者
  std::string group;     //<文件所属组
  std::string icon;      //<文件图标
  std::string iconColor; //<文件图标颜色
};

// 目录
class Dir {
private:
  std::unique_ptr<FileInfo> info;   //<改目录信息
  std::unique_ptr<FileInfo> parent; //<父目录信息
  std::list<FileInfo> files;   //<目录中所有文件以及文件夹信息
  std::list<std::string> dirs; //<递归只包含子目录
  bool (*less)(int, int);      //<定义排序时的比较规则
};
