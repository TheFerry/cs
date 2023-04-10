#include "longArranger.h"
#include "arranger.h"
#include "icons.h"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
core::LongArranger::LongArranger() {
  // 时间有4列
  colW_.resize(9, 0);
  colW_[8] = 2; // 图标默认占2格
  gap = 1;
}

void core::LongArranger::flush(std::string &buf) {
  // 第一次便利计算所有列中最长的宽度
  for (const auto &v : data_) {
    colW_[0] = colW_[0] < v->mode.size() ? v->mode.size() : colW_[0];
    colW_[1] = colW_[1] < v->owner.size() ? v->owner.size() : colW_[1];
    colW_[2] = colW_[2] < v->group.size() ? v->group.size() : colW_[2];
    colW_[3] = colW_[3] < v->size.size()
                   ? v->size.size()
                   : colW_[3];
    for (int i = 0; i < 4; ++i) {
      colW_[4 + i] = colW_[4 + i] < v->modtimeString[i].size()
                         ? v->modtimeString[i].size()
                         : colW_[4 + i];
    }
  }
  // 第二次循环录入数据
  std::ostringstream buffer;
  for (auto const &v : data_) {
    // 针对破碎的文件，输出红色报错
    char lineBuffer[512];
    buf += v->broken ? icon::IconInfo::getColor(220, 20, 60) : "";
    sprintf(lineBuffer, "%-*s%-*s%-*s%*s %-*s%-*s%-*s%-*s%-*s%s",
            colW_[0] + gap, v->mode.c_str(), colW_[1] + gap, v->owner.c_str(),
            colW_[2] + gap, v->group.c_str(), colW_[3] + gap, v->size.c_str(),
            colW_[4] + gap, v->modtimeString[0].c_str(), colW_[5] + gap,
            v->modtimeString[1].c_str(), colW_[6] + gap,
            v->modtimeString[2].c_str(), colW_[7] + gap,
            v->modtimeString[3].c_str(), colW_[8] + gap,
            (v->iconColor + v->icon + core::noColor + " ").c_str(),
            (v->name + v->indicator).c_str());

    if (v->targetLink) {
      size_t idx = strlen(lineBuffer);
      sprintf(lineBuffer + idx, "%-s",
              (" -> " + v->targetLink->iconColor + v->targetLink->icon +
               core::noColor + " " + icon::IconInfo::getColor(0, 191, 255) +
               v->targetLink->path + v->targetLink->indicator + core::noColor)
                  .c_str());
    }

    buf += lineBuffer;
    buf +='\n';
  }
}
