#include "arranger.h"
#include "flags.h"
#include "logger.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>
// 计算string中含有的汉子的个数
int calc_hz_count(std::string s) {
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
  std::ostringstream buf;
  LOG("size: " << cs[0] << " icon: " << cs[1] << " name: " << cs[2])
  // size
  if (cs[0] > 0) {
    buf << std::setw(cs[0]) << this->data[i][0] << "";
  }
  // icon
  if (showIcon) {
    buf << std::setw(cs[1]) << this->ic[i] << this->data[i][1] << noColor
        << ' ';
  }
  // name + indicate
  int chsN = calc_hz_count(data[i][2]);
  buf << std::left << std::setw(cs[2]+chsN) << this->data[i][2];
  std::string result = buf.str();
  buffer += result;
}

std::vector<int> core::arranger::colW(int begin, int end) {
  int sizeColumn = 0, nameColumn = 0;
  for (int i = begin; i < end; i++) {
    if (this->sizeW[i] > sizeColumn) {
      sizeColumn = this->sizeW[i];
    }
    if (this->nameW[i] > nameColumn) {
      nameColumn = this->nameW[i];
    }
  }
  std::vector<int> ans(3, 0);
  ans[0] = sizeColumn;
  ans[1] = showIcon ? 2 : 0;
  ans[2] = nameColumn;
  return ans;
}

void core::arranger::addRow(const std::vector<std::string> &args) {
  if (args.size() != this->cols) {
    return;
  }
  this->sizeW.push_back(args[0].size()); // args[0] 为size
  int chsN = calc_hz_count(args[2]);
  this->nameW.push_back(args[2].size()-chsN); // args[2] 为文件名
  if (!this->showIcon) {
    this->showIcon = args[1].size() > 0; // args[1] 为图标
  }
  this->data.push_back(args);
}

void core::arranger::iconColor(const std::string &color) {
  this->ic.push_back(color);
}

void core::arranger::flush(std::string &buf) {
  int dataN = this->data.size();
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
    if (totalWidth > termW || cols > dataN) { // 如果总宽度超过终端的宽度
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
