#include "flagParser.h"
#include <cstdint>
#include <unordered_map>

#include <iostream>

FlagParser* FlagParser::instance_ = nullptr;

std::unordered_map<char, int> FlagParser::check = {
    {'s', flag_s}, {'S', flag_S}, {'a', flag_a}, {'i', flag_i},
    {'l', flag_l}, {'A', flag_A}, {'c', flag_c}, {'h', flag_h},
    {'d', flag_d}, {'t', flag_t}, {'R', flag_R}, {'r', flag_r},
};

std::string FlagParser::helpText = {
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

FlagParser *FlagParser::flagParser() noexcept {
  if (FlagParser::instance_) {
    return FlagParser::instance_;
  } else {
    return nullptr;
  }
}

void FlagParser::initArgs(int argc, char **argv) {
  if (!FlagParser::instance_) {
    FlagParser::instance_ = new FlagParser(argc, argv);
  }else{
    return;
  }
  instance_->path_ = "./";
  bool ok = instance_->parse();
  if (!ok) {
    throw ParseErrorException("args parse error");
  }
}

int32_t FlagParser::flags() noexcept { return flags_; }
std::string FlagParser::path() noexcept { return path_; }

bool FlagParser::parse() noexcept {
  if(argc_<2){
    return true;
  }
  // 获取参数和路径参数
  std::string params;
  for (int i = 1; i < argc_; i++) {
    if (argv_[i][0] == '-') {
      params = argv_[i];
    } else {
      path_ = argv_[i];
    }
  }

  params= params.substr(1,- 1);
  // 解析参数中的值
  for (char c : params) {
    auto flagIter = check.find(c);
    if (flagIter != check.end()) {
      flags_ |= flagIter->second;
    } else {
      flags_ |= flag_h;
    }
  }
  return true;
}
