#pragma once
#include "term.h"
#include "file.h"
#include <vector>
namespace core {


/* 显示样式:
 * |       |      |      |      |        |     |       |
 * |<----->|<---->|<---->|<---->|<------>|<--->|<----->|
 * |权限   | 用户 |  组  | 大小 |更新时间|图标 | 文件名|
 *
 * 只有文件名长度可变,其他都是固定长度
 *
*/
class LongArranger : public Term {
private:
  //每一列的列宽
  std::vector<int> colW_;
  int gap{2};
public:
  void flush(std::string &buf) override;
  LongArranger();
};
} // namespace core
