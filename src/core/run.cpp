#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include "flags.h"
#include "../file/file.h"
int main(int argc, char *argv[]) {
  core::Flags& flag = core::Flags::getInstance(argc,argv);
  if(flag.getFlag()&core::Flags::flag_h){
    std::cout<<core::helpInfo<<std::endl;
    return 0;
  }
  file::Dir d(".");
  auto buf = d.print(); 
  std::string str;
  std::copy(buf.begin(),buf.end(),std::back_inserter(str));
  std::cout<<str;
}
