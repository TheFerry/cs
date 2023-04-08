#include "longArranger.h"
#include "arranger.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
core::LongArranger::LongArranger() {
  // 时间有4列
  colW_.resize(10, 0);
  colW_[8] = 2; // 图标默认占2格
  gap = 2;
}

void core::LongArranger::flush(std::string &buf) {
  // 第一次便利计算所有列中最长的宽度
  for (const auto &v : data_) {
    colW_[0] = colW_[0] < v->mode.size() ? v->mode.size() : colW_[0];
    colW_[1] = colW_[1] < v->owner.size() ? v->owner.size() : colW_[1];
    colW_[2] = colW_[2] < v->group.size() ? v->group.size() : colW_[2];
    colW_[3] = colW_[3] < std::to_string(v->size).size()
                   ? std::to_string(v->size).size()
                   : colW_[3];
    for (int i = 0; i < 4; ++i) {
      colW_[4 + i] = colW_[4 + i] < v->modtimeString[i].size()
                         ? v->modtimeString[i].size()
                         : colW_[4 + i];
    }
    colW_[9] = colW_[9] < v->name.size() ? v->name.size() : colW_[9];
  }
  // 第二次循环录入数据
  std::ostringstream buffer;
  for (auto const &v : data_) {
    buffer << std::left << std::setw(colW_[0] + gap) << v->mode
           << std::setw(colW_[1] + gap) << v->owner << std::setw(colW_[2] + gap)
           << v->group << std::setw(colW_[3] + gap) << v->size
           << std::setw(colW_[4] + gap) << v->modtimeString[0]
           << std::setw(colW_[5] + gap) << v->modtimeString[1]
           << std::setw(colW_[6] + gap) << v->modtimeString[2]
           << std::setw(colW_[7] + gap) << v->modtimeString[3]
           << std::setw(colW_[8]) << v->iconColor + v->icon
           << core::noColor + " " << std::setw(colW_[9])
           << v->name + v->indicator << '\n';
  }
  buf += buffer.str();
}
