#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace core {

/* 输出文件时每个文件包括3个部分
|<---->|<---->|<------------------------>|
| size | icon | name+extension+indicator |
*/
class arranger {
private:
  std::vector<std::vector<std::string>> data; //<传递给arranger的全部数据
  std::vector<int> nameW;                     //<每个文件名的宽度
  std::vector<int> sizeW;                     //<每个size的宽度
  std::vector<std::string> ic;                //<行的文件图标的颜色
  int cols;                                   //<从零开始的列数
  bool showIcon;                              //<是否显示图标
  int termW;                                  //<终端宽度
public:
  arranger(int termWidth);

  void addRow(std::vector<std::string> args);

  void iconColor(const std::string& color);

  void flush(std::vector<uint8_t>& buf);

  std::vector<int> colW(int begin,int end);
};
} // namespace core
