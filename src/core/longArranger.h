#pragma once
#include "term.h"
namespace core {


/* 显示样式:
 * |<----->|<---->|<---->|<---->|<------>|<--->|<----->|
 * |权限   | 用户 |  组  | 大小 |更新时间|图标 | 文件名|
 *
*/
class LongArranger : public Term {
private:
public:
  void flush(std::string &buf) override;
  void iconColor(const std::string &color) override;
  void addRow(const std::vector<std::string> &args) override;
  LongArranger(){}
};
} // namespace core
