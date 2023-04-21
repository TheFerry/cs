#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>

class ParseErrorException: public std::exception {
public:
  ParseErrorException(const std::string &message) : message_(message) {}
  virtual const char *what() const noexcept override {
    return message_.c_str();
  }

private:
  std::string message_;
};

class FlagParser {
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
    flag_S = flag_s << 1, // 通过文件大小排序
  };
  static std::unordered_map<char,int> check;
  static FlagParser *flagParser()noexcept;
  static void initArgs(int argc, char **argv);
  int flags()noexcept;
  std::string path()noexcept;
  static std::string helpText;
private:
  static FlagParser* instance_;
  explicit FlagParser(int argc, char **argv)noexcept : argc_(argc), argv_(argv){};
  bool parse() noexcept;
  char **argv_;
  int argc_;
  int flags_;
  std::string path_;
};
