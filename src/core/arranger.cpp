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
#include <sstream>
#include <vector>
/// 计算总宽度
int widthsSum(std::vector<std::vector<int>> w, int p) {
  int s = 0;
  for (const auto &v : w) {
    s += v[0] + v[1] + v[2] + p;
  }
  s -= p;
  return s;
}

core::arranger::arranger(int termWidth) {
  this->cols = 3; // 默认每个文件显示三列信息 |size|icon|name ext indi|
  this->termW = termWidth;
  auto flags = core::Flags::getInstance().getFlag();
  if (!(flags & core::Flags::flag_i)) {
    this->showIcon = true;
  } else {
    this->showIcon = false;
  }
}

// 将数据写入到缓冲区中
void core::arranger::printCell(std::vector<uint8_t> &buffer, int i,
                               std::vector<int> cs) {
  std::ostringstream buf;
  if (cs[0] > 0) {
    buf << std::setw(cs[0]) << std::left << this->data[i][0] << brailEmpty;
  }
  if (showIcon) {
    buf << std::setw(cs[1]) << std::left << this->ic[i] << this->data[i][1]
        << noColor<<brailEmpty;
  }
  buf << std::setw(cs[2]) << std::left << this->data[i][2] << noColor
      << brailEmpty;
  std::string result = buf.str();
  std::copy(result.begin(), result.end(), std::back_inserter(buffer));
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
  std::vector<int> ans(3);
  if (sizeColumn > 0) {
    ans[0] = sizeColumn;
  }
  if (this->showIcon) {
    ans[1] = 2;
  } else {
    ans[1] = 0;
  }
  if (nameColumn > 0)
    ans[2] = nameColumn;
  return ans;
}

void core::arranger::addRow(std::vector<std::string> args) {
  if (args.size() != this->cols) {
    return;
  }
  this->sizeW.push_back(args[0].size()); // args[0] 为size
  this->nameW.push_back(args[2].size()); // args[2] 为文件名
  if (!this->showIcon) {
    this->showIcon = args[1].size() > 0; // args[1] 为图标
  }
  this->data.push_back(args);
}

void core::arranger::iconColor(const std::string &color) {
  this->ic.push_back(color);
}

void core::arranger::flush(std::vector<uint8_t> &buf) {
  int dataN = this->data.size();
  if (dataN == 0) {
    return;
  }
  int pad = 2; // 间隔

  std::vector<std::vector<int>> columnW; // 每一列的宽度

  std::vector<std::vector<int>> widths; // 储存最终计算得出的每一列的宽度

  int prevj = 0; // 上一次遍历中每一列的条目数

  while (true) {
    columnW.push_back({0, 0, 0});
    int cols = columnW.size(); // 尝试将列出加1
    int j = std::ceil((float)dataN / cols); // 计算此时每一列应有多少条目
    /* if (prevj == j) { */
    /*   continue; */
    /* } */

    int begin = 0; // 列的起始值
    int end = j;   // 列的结束值

    // 该列实际列宽由该列中最宽的元素决定
    for (int i = 0; i < cols && end < dataN; i++) {
      columnW[i] = this->colW(begin, end); // 获取该列最宽的宽度
      begin = end;
      end = end + j;
    }
    // 对于最后一列未满的情况
    if (end - j < dataN) {
      columnW[cols - 1] = this->colW(end - j, dataN);
    }

    prevj = j;

    // 计算出总宽度
    int totalWidth = widthsSum(columnW, pad);
    LOG("totalWidth:"<<totalWidth)
    if (totalWidth > this->termW ) { // 如果总宽度超过终端的宽度
      if (widths.size() == 0) {
        widths.resize(columnW.size());
        for (int i = 0; i < columnW.size(); i++) {
          widths[i] = columnW[i];
        }
      }
      break;
    }

    widths.resize(columnW.size());
    std::copy(columnW.begin(), columnW.end(), widths.begin());
  }
  int rows = std::ceil((float)dataN / widths.size());
  LOG("final width :"<<widthsSum(widths,pad))
  for (int i = 0; i < rows; i++) {
    int p = pad;
    for (int j = 0; j < widths.size(); j++) {
      if (i + j * rows >= dataN)
        continue;
      if (j == widths.size() - 1)
        p = 0;
      this->printCell(buf, i + j * rows, widths[j]);
      std::stringstream oss;
      oss << std::setw(p) << brailEmpty;
      auto padding = oss.str();
      std::copy(padding.begin(), padding.end(), std::back_inserter(buf));
    }
    buf.push_back('\n');
  }
}
