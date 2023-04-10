#pragma once
#include "cxxopts.hpp"
#include <cstdint>
#include <memory>
namespace core {

// 程序运行时接受的参数
class Flags {
private:
  uint32_t m_flag; // 用位表示解析后的参数
  std::unique_ptr<cxxopts::Options> options;
  Flags(int, char *[]);
  std::string path_;

public:
  enum {
    flag_l = 0x01,        // 列出文件详细信息
    flag_a = flag_l << 1, // 列出所有文件
    flag_i = flag_a << 1, // 不显示图标信息
    flag_c = flag_i << 1, // 不显示颜色
    flag_h = flag_c << 1, // 显示帮助信息
    flag_d = flag_h << 1, // 只显示目录
    flag_r = flag_d << 1, // 倒序显示文件和目录
    flag_t = flag_r << 1, // 按照修改时间顺序排列，最新的在最前面
    flag_A = flag_t << 1, // 与 -a同理，但是不显示 . 和 ..
    flag_R = flag_A << 1, // 递归显示目录中的所有文件和子目录
    flag_s = flag_R << 1, // 显示大小
  };
  std::string path() { return path_; }
  static Flags &getInstance(int argc, char *argv[]);
  static Flags &getInstance() {
    char *argv[] = {(char *)"cs"};
    return getInstance(1, argv);
  }
  uint32_t getFlag() const { return m_flag; }
};

const std::string helpInfo{
    "\nA modern ls command with icons and colors,making ls more beautiful\n\n"
    "Usage: cs -[FLAGS]\n\n"
    "Possiable value for [FLAGS]:\n"
    "\t-l long      :list detail infomation\n"
    "\t-a all       :list all files\n"
    "\t-A All       :show all file except '.' and '..'\n"
    "\t-i icon      :hide the icons\n"
    "\t-d directory :only show directories\n"
    "\t-r reverse   :reverse sorting methed\n"
    "\t-c color     :disable colors\n"
    "\t-h help      :show help documentation\n"};
} // namespace core
