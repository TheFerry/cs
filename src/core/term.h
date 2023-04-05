#pragma once
#include <string>
#include <vector>
namespace core {

class Term {
public:
  virtual void flush(std::string &buf) = 0;
  virtual void iconColor(const std::string &color) = 0;
  virtual void addRow(const std::vector<std::string> &args) = 0;
  virtual ~Term() = default;
};
} // namespace core
