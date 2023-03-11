#include<iostream>
#include "icons.h"
#include<sys/ioctl.h>
void test(){
  struct winsize size;
  ioctl(stdin->_fileno, TIOCGWINSZ,&size);
  std::cout<<"winsize:"<<size.ws_col<<" "<<size.ws_row<<std::endl;
  /* for(auto& item:icon::IncoSet){ */
  /*   std::cout<<item.first<<" "<<item.second.getColor()<< item.second.getGraph()<<"\033[0m"<<std::endl; */
  /* } */
}
int main(){
  test();
  return 0;
}
