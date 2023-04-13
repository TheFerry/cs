#include "arranger.h"
#include "flags.h"
#include "logger.h"
#include "term.h"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
// 计算string中含有的汉字的个数
int calc_hz_count(const std::string &s) {
  int sum = 0;
  for (char c : s) {
    if (c < 0)
      sum++;
  }
  sum /= 3;
  return sum;
}

/// 计算总宽度
inline int widthsSum(const std::vector<std::vector<int>> &w, int p) {
  int s = 0;
  for (auto &v : w) {
    s += v[0] + v[1] + v[2] + p;
  }
  s -= p;
  return s;
}

core::arranger::arranger(int termWidth) {
  this->cols = 3; // 默认每个文件显示三列信息 |size|icon|name ext indi|
  this->termW = termWidth;
  const auto &flags = core::Flags::getInstance().getFlag();
  if (!(flags & core::Flags::flag_i)) {
    this->showIcon = true;
  } else {
    this->showIcon = false;
  }
}

// 将数据写入到缓冲区中
void core::arranger::printCell(std::string &buffer, int i,
                               const std::vector<int> &cs) {
  int chsN = calc_hz_count(data_[i]->name);
  char cellBuffer[512];
  sprintf(cellBuffer, "%-*s%-*s%-*s", cs[0], cs[0]?(data_[i]->size+" ").c_str():"", cs[1],
          cs[1]?(data_[i]->iconColor + data_[i]->icon.c_str() + noColor + " ").c_str():"",
          cs[2] + chsN, (data_[i]->name+data_[i]->indicator).c_str());
  buffer += cellBuffer;
}
std::vector<int> core::arranger::colW(int begin, int end) {
  int sizeColumn = 0, nameColumn = 0;
  for (int i = begin; i < end; i++) {
    if (Flags::getInstance().getFlag() & Flags::flag_s) {
      if (this->data_[i]->size.size() > sizeColumn) {
        sizeColumn = this->data_[i]->size.size();
      }
    }
    if (data_[i]->name.size() + data_[i]->indicator.size() > nameColumn) {
      nameColumn = data_[i]->name.size() + data_[i]->indicator.size();
    }
  }
  return {sizeColumn?sizeColumn+1:0, showIcon ? 2 : 0, nameColumn};
}


void core::arranger::flush(std::string &buf) {
  int dataN = data_.size();
  if (dataN == 0) {
    return;
  }
  int pad = 2; // 间隔

  std::vector<std::vector<int>> columnW; // 每一列的宽度

  std::vector<std::vector<int>> widths; // 储存最终计算得出的每一列的宽度
  int cols = 0;
  int prevj = 0;
  while (cols < dataN) {
    cols++;                                 // 尝试将列出加1
    int j = std::ceil((float)dataN / cols); // 计算此时每一列应有多少条目
    if (j == prevj)
      continue;
    columnW.resize(cols, {0, 0, 0});
    prevj = j;
    int begin = 0; // 列的起始值
    int end = j;   // 列的结束值

    // 该列实际列宽由该列中最宽的元素决定
    for (int i = 0; i < cols && end <= dataN; i++) {
      columnW[i] = this->colW(begin, end); // 获取该列最宽的宽度
      begin = end;
      end = end + j;
    }
    // 对于最后一列未满的情况
    if (begin < dataN) {
      columnW[cols - 1] = this->colW(begin, dataN);
    }

    // 计算出总宽度
    int totalWidth = widthsSum(columnW, pad);
    if (totalWidth >= termW || cols > dataN) { // 如果总宽度超过终端的宽度
      break;
    }
    widths = columnW;
  }

  int rows = std::ceil((float)dataN / widths.size());
  for (int i = 0; i < rows; i++) {
    int p = pad;
    for (int j = 0; j < widths.size(); j++) {
      if (i + j * rows >= dataN)
        break;
      if (j == widths.size() - 1)
        p = 0;
      else
        p = pad;
      printCell(buf, i + j * rows, widths[j]);
      buf += p > 0 ? "  " : "";
    }
    buf += '\n';
  }
}

void core::arranger::setData(std::vector<file::FileInfo *> &files) {
  Term::setData(files);
}
