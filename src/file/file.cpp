#include "file.h"
const std::string Item::getName() const {
  auto idx_end = path.rfind('/');
  return path.substr(idx_end + 1);
}

Item::Item() {
  fileType = "common";
  isHide = false;
  isExecutable = false;
  if (path.size() != 0)
    path = ".";
}
