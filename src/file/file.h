#include <iostream>
#include <string>
class IconDecorator;
class ColorDecorator;
/// 任何文件的基类
class Item {
protected:
  bool decoratedByColor; // 是否被装饰有颜色
  bool decoratedByIcon;  // 是否被装饰有图标
  bool isHide;           // 文件是否隐藏
  bool isExecutable;     // 文件是否有可执行权限
  std::string fileType;  // 文件类型
  std::string path;
  friend IconDecorator;
  friend ColorDecorator;

public:
  const std::string getPath() const { return path; }
  virtual const std::string getName() const;
  Item(std::string Path) : path(Path) {}
  Item();
  virtual ~Item() = default;
  virtual const std::string getType() const = 0;
  void printSelf() {
    std::cout.setf(std::ios_base::left);
    std::cout << getName() << "\t";
  }
  //一个文件只能被装饰一个颜色，被装饰一个图标
  virtual bool isDecoratedByColor() { return decoratedByColor; }
  virtual bool isDecoratedByIcon() { return decoratedByIcon; }
};
