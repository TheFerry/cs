#include "../file/file.h"
#include "flags.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#ifdef __MINGW32__
#include <windows.h>
#endif

#ifdef _MSC_VER
#include <codecvt>
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
  std::string str;
  std::copy(buf.begin(), buf.end(), std::back_inserter(str));

#ifdef _MSC_VER
  std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
  std::wstring wstr = converter.from_bytes(str);
  std::wcout << wstr;
#else
  std::cout << str;
#endif
}
