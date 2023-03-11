#include<iostream>
#include "icons.h"
void test(){
  for(auto& item:icon::IncoSet){
    std::cout<<item.first<<" "<<item.second.getColor()<< item.second.getGraph()<<"\033[0m"<<std::endl;
  }
}
int main(){
  test();
  return 0;
}
