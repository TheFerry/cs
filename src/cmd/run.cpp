#include "file.h"
#include "flags.h"
#include <algorithm>
#include <exception>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <string>
int main(int argc, char *argv[]) {
  core::Flags &flag = core::Flags::getInstance(argc, argv);
  if (flag.getFlag() & core::Flags::flag_h) {
    std::cout << core::helpInfo << std::endl;
    return 0;
  }
  file::Dir *dir;
  try{
    dir = new file::Dir(flag.path());
  }catch(std::filesystem::filesystem_error&e){
    std::cout<<e.what()<<std::endl;
    return 1;
  }
  auto buf = dir->print();
  delete dir;
  std::cout << buf;
  return 0;
}
