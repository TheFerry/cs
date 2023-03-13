#pragma once
#include <bits/types/time_t.h>
#include <memory>
#include <string>
#include <filesystem>
#include <vector>
namespace file {

/// 文件信息
struct FileInfo {
  // 不同文件有不同标志如果是目录‘/’，如果是管道‘|’，如果是链接‘@’，如果是socket‘=’,如果可执行‘*’
  std::string indicator;
  std::filesystem::file_time_type modTime;        //<修改时间
  std::string name;      //<文件名
  std::string extension; //<文件拓展名
  size_t size;           //<文件大小
  std::string mode;      //<文件权限
  int modeBits;     //<用位表示文件权限
  std::string owner;     //<文件所有者
  std::string group;     //<文件所属组
  std::string icon;      //<文件图标
  std::string iconColor; //<文件图标颜色
};
// 目录
class Dir {
private:
  FileInfo info;   //<改目录信息
  FileInfo parent; //<父目录信息
  std::vector<FileInfo> files;   //<目录中所有文件以及文件夹信息
  std::vector<std::string> dirs; //<递归只包含子目录
  bool (*less)(int, int);      //<定义排序时的比较规则

  //获取指定文件或目录的大小
  size_t getSize(const std::filesystem::path& path) const;

  //获取后缀信息
  std::string getIncidator(const std::filesystem::path& path)const;

  //获取图标以及颜色信息
  std::pair<std::string,std::string> getIcon(const std::string& name,const std::string& extension,const std::string& indicator);

public:
  Dir(std::string d);
  std::vector<uint8_t> print();
};
} // namespace file
