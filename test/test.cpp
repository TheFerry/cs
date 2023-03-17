#include "arranger.h"
#include "iconDirs.h"
#include "iconExtension.h"
#include "iconFilename.h"
#include "icons.h"
#include <cstdint>
#include <iostream>
#ifdef __linux__
#include <sys/ioctl.h>
#endif
#ifdef _WIN32
#include <Windows.h>
#endif

void test() {
#ifdef __MINGW32__
  SetConsoleOutputCP(CP_UTF8);
#endif

  int termWidth = 80;
#ifdef __linux__
  winsize size;
  ioctl(stdin->_fileno, TIOCGWINSZ, &size);
  termWidth = size.ws_col;
#endif

#ifdef _WIN32
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  termWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
#endif

  core::arranger a(termWidth);
  std::string buf;
  for (auto &[k, v] : icon::iconSet) {
    a.addRow({"", v.getGraph(), k});
    a.iconColor(v.getColor());
  }
  a.flush(buf);
  std::cout<<buf;
  std::cout << std::endl;
  buf.clear();
  std::cout << "iconDirs" << std::endl;
  for (auto &[k, v] : icon::iconDirs) {
    a.addRow({"", v.getGraph(), k});
    a.iconColor(v.getColor());
  }
  a.flush(buf);
  std::cout<<buf;
  buf.clear();
  std::cout << std::endl;
  std::cout << "iconExtension" << std::endl;
  for (auto &[k, v] : icon::iconExtension) {
    a.addRow({"", v.getGraph(), k});
    a.iconColor(v.getColor());
  }
  a.flush(buf);
  std::cout<<buf;
  std::cout << std::endl;
  buf.clear();

  std::cout << "iconFilename" << std::endl;
  for (auto &[k, v] : icon::iconFilename) {
    a.addRow({"", v.getGraph(), k});
    a.iconColor(v.getColor());
  }
  a.flush(buf);
  std::cout<<buf;
  std::cout << std::endl;
}
int main() {
  test();
  return 0;
}
