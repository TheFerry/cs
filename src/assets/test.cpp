#include "../core/arranger.h"
#include "iconDirs.h"
#include "iconExtension.h"
#include "iconFilename.h"
#include "icons.h"
#include <cstdint>
#include <iostream>
#include <sys/ioctl.h>
void test() {
  struct winsize size;
  ioctl(stdin->_fileno, TIOCGWINSZ, &size);
  std::cout << "list al icons..." << std::endl;
  core::arranger a(size.ws_col);
  std::vector<uint8_t> buf;
  for (auto &[k, v] : icon::iconSet) {
    a.addRow({"", v.getGraph(), k});
    a.iconColor(v.getColor());
  }
  a.flush(buf);
  for (uint8_t v : buf) {
    std::cout << static_cast<char>(v);
  }
  std::cout << std::endl;
  buf.clear();
  std::cout << "iconDirs" << std::endl;
  for (auto &[k, v] : icon::iconDirs) {
    a.addRow({"", v.getGraph(), k});
    a.iconColor(v.getColor());
  }
  a.flush(buf);
  for (uint8_t v : buf) {
    std::cout << static_cast<char>(v);
  }
  buf.clear();
  std::cout << std::endl;
  std::cout << "iconExtension" << std::endl;
  for (auto &[k, v] : icon::iconExtension) {
    a.addRow({"", v.getGraph(), k});
    a.iconColor(v.getColor());
  }
  a.flush(buf);
  for (uint8_t v : buf) {
    std::cout << static_cast<char>(v);
  }
  std::cout << std::endl;
  buf.clear();

  std::cout << "iconFilename" << std::endl;
  for (auto &[k, v] : icon::iconFilename) {
    a.addRow({"", v.getGraph(), k});
    a.iconColor(v.getColor());
  }
  a.flush(buf);
  for (uint8_t v : buf) {
    std::cout << static_cast<char>(v);
  }
  std::cout << std::endl;

}
int main() {
  test();
  return 0;
}
