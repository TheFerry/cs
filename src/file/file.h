#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <sys/stat.h>
#include <vector>
namespace file {

/// 文件信息
struct FileInfo {
  // 不同文件有不同标志如果是目录‘/’，如果是管道‘|’，如果是链接‘@’，如果是socket‘=’,如果可执行‘*’
  std::string indicator;
  /* std::filesystem::file_time_type modTime;        //<修改时间 */
  // 时间由四个元素组成，年，月，日，具体时间
  std::string modtimeString{};
  std::string name{};            //<文件名
  std::string path{};            //<文件路径
  std::string extension{};       //<文件拓展名
  bool isDir{false};             //<是否是目录
  std::string sizeStr{};         //<文件大小显示的字符串
  std::uintmax_t size{0};        //<实际文件大小
  std::string mode{};            //<文件权限
  std::string owner{};           //<文件所有者
  std::string group{};           //<文件所属组
  std::string icon{};            //<文件图标
  std::string iconColor{};       //<文件图标颜色
  FileInfo *targetLink{nullptr}; //<对于链接文件的实际文件
  bool broken{false};            //<文件是否破损(异常的链接)
  struct stat filestat;
};

class DirException : public std::exception {
public:
  DirException(const std::string &message) : message_(message) {}
  virtual const char *what() const noexcept override {
    return message_.c_str();
  }

private:
  std::string message_;
};

// 目录
class Dir {
private:
  FileInfo *info;                //<改目录信息
  FileInfo *parent;              //<父目录信息
  std::vector<FileInfo *> files; //<目录中所有文件以及文件夹信息
  std::vector<std::string> dirs; //<递归只包含子目录
  bool (*compare)(const FileInfo*, const FileInfo*);        //<定义排序时的比较规则
  void getTimeString(FileInfo &info);
  // 获取指定文件或目录的大小
  void getSize(FileInfo &info);
  // 获取后缀信息
  void getIncidator(FileInfo &info) const;
  // 获取owner和group
  void getOwnerAndGroup(FileInfo &info);
  // 获取所有权限
  void getMode(FileInfo &inco);
  // 获取链接的实际文件
  void getLinkTarget(FileInfo &info);
  // 获取图标以及颜色信息
  std::pair<std::string, std::string> getIcon(const FileInfo &info) const;
  // 只填充path字段，自动填充剩余字段
  bool encapsulationFileInfo(FileInfo &info);
  // 生成排序算法
  void generateSortMethed();

public:
  ~Dir() = default;
  Dir(std::string d);
  std::string print();
};
} // namespace file
