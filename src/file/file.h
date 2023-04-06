#pragma once
#include <filesystem>
#include <memory>
#include <string>
#include <vector>
namespace file {

/// 文件信息
struct FileInfo {
  // 不同文件有不同标志如果是目录‘/’，如果是管道‘|’，如果是链接‘@’，如果是socket‘=’,如果可执行‘*’
  std::string indicator;
  /* std::filesystem::file_time_type modTime;        //<修改时间 */
  // 时间由四个元素组成，年，月，日，具体时间
  std::vector<std::string> modtimeString;
  std::string name;                    //<文件名
  std::string extension;               //<文件拓展名
  bool isDir;                          //<是否是目录
  size_t size;                         //<文件大小
  std::string mode;                    //<文件权限
  std::filesystem::perms permission;   //<用位表示文件权限
  std::filesystem::file_type fileType; // 文件类型
  std::string owner;                   //<文件所有者
  std::string group;                   //<文件所属组
  std::string icon;                    //<文件图标
  std::string iconColor;               //<文件图标颜色
};
// 目录
class Dir {
private:
  FileInfo *info;                //<改目录信息
  FileInfo *parent;              //<父目录信息
  std::vector<FileInfo *> files; //<目录中所有文件以及文件夹信息
  std::vector<std::string> dirs; //<递归只包含子目录
  bool (*less)(int, int);        //<定义排序时的比较规则

  template <typename TP> std::vector<std::string> getTimeString(TP tp);
  // 获取指定文件或目录的大小
  void getSize(FileInfo &info);

  // 获取后缀信息
  void getIncidator(FileInfo &info) const;
  // 获取owner和group
  void getOwnerAndGroup(FileInfo &info);
  // 获取所有权限
  void getMode(FileInfo &inco);
  // 获取图标以及颜色信息
  std::pair<std::string, std::string> getIcon(const std::string &name,
                                              const std::string &extension,
                                              const std::string &indicator);

public:
  ~Dir();
  Dir(std::string d);
  std::string print();
};
} // namespace file
