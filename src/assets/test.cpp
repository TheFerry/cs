#include <cstdint>
#include<iostream>
#include "icons.h"
#include<sys/ioctl.h>
#include"../core/arranger.h"
void test(){
  struct winsize size;
  ioctl(stdin->_fileno, TIOCGWINSZ,&size);
  std::cout<<"list al icons..."<<std::endl;
  core::arranger a(size.ws_col);
  std::vector<uint8_t> buf;
  for(auto& v:icon::IncoSet){
    a.addRow({"  " ,v.second.getGraph(),v.first.c_str()});
    a.iconColor(v.second.getColor());
  }
  a.flush(buf);
  for(uint8_t v:buf){
    std::cout<<static_cast<char>(v);
  }
  std::cout<<std::endl;
}
int main(){
  test();
  return 0;
}
