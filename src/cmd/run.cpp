#include "file.h"
#include "flags.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

#ifdef __MINGW32__
#include <windows.h>
#endif

int main(int argc, char *argv[]) {
#ifdef __MINGW32__
  SetConsoleOutputCP(CP_UTF8);
#endif

  core::Flags &flag = core::Flags::getInstance(argc, argv);
  if (flag.getFlag() & core::Flags::flag_h) {
    std::cout << core::helpInfo << std::endl;
    return 0;
  }
  file::Dir d(".");
  auto buf = d.print();
  std::cout << buf;
}
