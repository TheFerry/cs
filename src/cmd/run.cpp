#include "file.h"
#include "flagParser.h"
#include <algorithm>
#include <exception>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <string>
int main(int argc, char *argv[]) {
  FlagParser::initArgs(argc, argv);
  if (FlagParser::flagParser()->flags() & FlagParser::flag_h) {
    std::cout << FlagParser::helpText << std::endl;
    return 0;
  }
  file::Dir *dir;
  try{
    dir = new file::Dir(FlagParser::flagParser()->path());
  }catch(std::exception&e){
    std::cout<<e.what()<<std::endl;
    return 1;
  }
  auto buf = dir->print();
  delete dir;
  std::cout << buf;
  return 0;
}
