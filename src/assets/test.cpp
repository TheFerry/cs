#include <cstdint>
#include<iostream>
#include "icons.h"
#include<sys/ioctl.h>
#include"../core/arranger.h"
void test(){
  struct winsize size;
  ioctl(stdin->_fileno, TIOCGWINSZ,&size);
  std::cout<<"winsize:"<<size.ws_col<<" "<<size.ws_row<<std::endl;
  /* for(auto& item:icon::IncoSet){ */
  /*   std::cout<<item.first<<" "<<item.second.getColor()<< item.second.getGraph()<<"\033[0m"<<std::endl; */
  /* } */
  core::arranger a(size.ws_col);
  std::vector<uint8_t> buf;
  for(auto& v:icon::IncoSet){
    a.addRow({"     ",v.second.getGraph(),v.first});
    a.iconColor(v.second.getColor());
  }
  a.flush(buf);
  std::cout<<"buf size:"<<buf.size()<<std::endl;
  for(uint8_t v:buf){
    std::cout<<static_cast<char>(v);
  }
  std::cout<<std::endl;
}
int main(){
  test();
  return 0;
}
