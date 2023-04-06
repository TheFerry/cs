#pragma once
#include "file.h"
#include <string>
#include <vector>
namespace core {

class Term {
protected:
  std::vector<file::FileInfo *> data_;

public:
  virtual void setData(std::vector<file::FileInfo *> &data) {
    for (auto const &v : data) {
      data_.push_back(v);
    }
  }
  virtual void flush(std::string &buf) = 0;
  virtual ~Term() = default;
};
} // namespace core
