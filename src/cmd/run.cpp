#include "file.h"
#include "flags.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

#ifdef __MINGW32__
#include <windows.h>
#endif

#ifdef _MSC_VER
#include<sstream>
#include<codecvt>
#include<Windows.h>
inline
std::wstring StringToWString(const std::string& str)
{
  int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
  wchar_t* wide = new wchar_t[len + 1];
  memset(wide, '\0', sizeof(wchar_t) * (len + 1));
  MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wide, len);
  std::wstring w_str(wide);
  delete[] wide;
  return w_str;
}
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
  std::string str(buf.begin(),buf.end());

#ifdef _MSC_VER
  SetConsoleOutputCP(CP_UTF8);
  std::wstring wstr = StringToWString(str);
  std::wcout << wstr;
#else
  std::cout << str;
#endif
}
