#include "arranger.h"
#include <cmath>

core::arranger::arranger(int termWidth){
  this->cols = 3;               //默认每个文件显示三列信息 |size|icon|name ext indi|
  this->termW = termWidth;
}


std::vector<int> core::arranger::colW(int begin, int end){
  int sizeColumn=0,nameColumn=0;
  for(int i=begin;i<end;i++){
    if(this->sizeW[i]>sizeColumn){
      sizeColumn = this->sizeW[i];
    }
    if(this->nameW[i]>nameColumn){
      nameColumn = this->nameW[i];
    }
  }
  std::vector<int> ans;
  if(sizeColumn>0){
    ans[0] = sizeColumn+1;
  }
  if( this->showIcon){
    ans[1] = 2;
  }else{
    ans[1] = 0;
  }
  ans[2] = nameColumn;
  return ans;
}

void core::arranger::addRow(std::vector<std::string> args){
  if(args.size()!= this->cols + 1){
    return;
  }
  this->sizeW.push_back(args[0].size());//args[0] 为size
  this->nameW.push_back(args[2].size());//args[2] 为文件名
  if(!this->showIcon){
    this->showIcon = args[1].size()>0;//args[1] 为图标
  }
  this->data.push_back(args);
}

void core::arranger::iconColor(const std::string& color){
  this->ic.push_back(color);
}

void core::arranger::flush(std::vector<uint8_t> &buf){
  int dataN = this->data.size();
  if(dataN == 0){
    return;
  }
  int pad = 2;//间隔

  std::vector<std::vector<int>> columnW;//每一列的宽度
  
  std::vector<std::vector<int>> widths;

  int prevj = 0;

  while(true){
    int cols = columnW.size()+1;
    columnW.push_back({0,0,0,0});
    int j = std::ceil((float)dataN/cols);
    if(prevj == j){
      continue;
    }

    int begin = 0;//列的起始值
    int end = j;//列的结束值
    
    for(int i = 0;i<cols&&end<=dataN;i++){
      columnW[i] = this->colW(begin, end);
      begin = end;
      end = end+j;
    }

    if(end-j < dataN){
      columnW[cols-1] = this->colW(end-j, dataN);
    }

    prevj = j;


  }
}
