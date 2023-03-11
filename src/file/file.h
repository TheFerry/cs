#pragma once
#include <bits/types/time_t.h>
#include <list>
#include <memory>
#include <string>

/// 文件信息
class FileInfo {
private:
  // 不同文件有不同标志如果是目录‘/’，如果是管道‘|’，如果是链接‘@’，如果是socket‘=’,如果可执行‘*’
  std::string indicator;
  time_t modTime;        //<修改时间
  std::string name;      //<文件名
  std::string extension; //<文件拓展名
  size_t size;           //<文件大小
  std::string mode;      //<文件权限
  uint32_t modeBits;     //<用位表示文件权限
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
