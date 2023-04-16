#include "arranger.h"
#include "file.h"
#include "iconDirs.h"
#include "iconExtension.h"
#include "iconFilename.h"
#include "icons.h"
#include <cstdint>
#include <iostream>
#include <sys/ioctl.h>

void test() {
  int termWidth = 80;
  winsize size;
  ioctl(stdin->_fileno, TIOCGWINSZ, &size);
  termWidth = size.ws_col;
  core::arranger a(termWidth);
  std::string buf;
  std::vector<file::FileInfo*> files;
  for(auto iconInfo:icon::iconSet){
    auto tmp = new file::FileInfo;
    tmp->name = iconInfo.first;
    tmp->iconColor = iconInfo.second.getColor();
    tmp->icon = iconInfo.second.getGraph();
    files.push_back(tmp);
  }
  a.setData(files); 
  a.flush(buf);
  std::cout<<buf<<std::endl;
}
int main() {
  test();
  return 0;
}
