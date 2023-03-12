#include <iostream>
#include <string>
#include "flags.h"
#include "../file/file.h"
int main(int argc, char *argv[]) {
  core::Flags& flag = core::Flags::getInstance(argc,argv);
  file::Dir d(".");
  auto buf = d.print(); 
  for(char c:buf){
    std::cout<<c;
  }
}
