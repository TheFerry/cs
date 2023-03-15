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
/// 计算总宽度
int widthsSum(std::vector<std::vector<int>> w, int p) {
  int s = 0;
  for (auto &v : w) {
    s += std::accumulate(v.begin(), v.end(), 0) + p;
  }
  s -= p;
  return s;
}

core::arranger::arranger(int termWidth) {
  this->cols = 3; // 默认每个文件显示三列信息 |size|icon|name ext indi|
  this->termW = termWidth;
  const auto& flags = core::Flags::getInstance().getFlag();
  if (!(flags & core::Flags::flag_i)) {
    this->showIcon = true;
  } else {
    this->showIcon = false;
  }
}

// 将数据写入到缓冲区中
void core::arranger::printCell(std::vector<uint8_t> &buffer, int i,
                               const std::vector<int>& cs) {
  std::ostringstream buf;
  // size
  if (cs[0] > 0) {
    buf << std::setw(cs[0]) << this->data[i][0] << "";
  }
  // icon
  if (showIcon) {
    LOG("Icon size: " << cs[1])
    buf << std::setw(cs[1]) << this->ic[i] << this->data[i][1] << noColor
        << " ";
  }
  // name + indicate
  buf << std::left << std::setw(cs[2]) << this->data[i][2] << noColor << "";
  std::string result = buf.str();
  buffer.insert(buffer.end(), result.begin(), result.end());
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

void core::arranger::addRow(const std::vector<std::string>& args) {
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
  LOG("dataN: " << dataN)
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
      LOG("begin: " << begin << " end: " << end)
      begin = end;
      end = end + j;
    }
    // 对于最后一列未满的情况
    if (begin < dataN) {
      columnW[cols - 1] = this->colW(begin, dataN);
      LOG("end row begin: " << begin << " end: " << dataN)
    }

    // 计算出总宽度
    int totalWidth = widthsSum(columnW, pad);
    if (totalWidth > this->termW || cols > dataN) { // 如果总宽度超过终端的宽度
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
      std::stringstream oss;
      oss << std::setw(p) << "";
      auto padding = oss.str();
      buf.insert(buf.end(), padding.begin(), padding.end());
    }
    buf.push_back('\n');
  }
}
