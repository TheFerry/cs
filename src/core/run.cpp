#include <filesystem>
#include "err.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "../file/file.h"
int main(int argc, char *argv[]) {
  std::string path{};
  if (argc == 1) {
    path = ".";
  } else if (argc == 2) {
    path = argv[1];
  } else {
    std::cout << "用法：\n"
              << "\t" << argv[0] << "[path]" << std::endl;
    return -1;
  }

  std::cout<<".."<<std::endl;
}
