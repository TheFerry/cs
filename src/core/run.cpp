#include "../file/file.h"
#include "flags.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
int main(int argc, char *argv[]) {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif
  core::Flags &flag = core::Flags::getInstance(argc, argv);
  if (flag.getFlag() & core::Flags::flag_h) {
    std::cout << core::helpInfo << std::endl;
    return 0;
  }
  file::Dir d(".");
  auto buf = d.print();
  std::string str;
  std::copy(buf.begin(), buf.end(), std::back_inserter(str));
  std::cout << str;
}
