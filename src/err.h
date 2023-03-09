#pragma once
#include <stdexcept>
#include <string>
/// 目录相关的错误
class DirectoryErr : public std::runtime_error {
private:
  std::string message;

public:
  DirectoryErr(const std::string &msg)
      : std::runtime_error(msg), message(msg) {}
};

