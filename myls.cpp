#include "config.h"
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
/// 目录相关的错误
class DirectoryErr : public std::runtime_error {
private:
  std::string message;

public:
  DirectoryErr(const std::string &msg)
      : std::runtime_error(msg), message(msg) {}
};
//============================================================
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
  virtual const std::string getName() const {
    auto idx_end = path.rfind('/');
    return path.substr(idx_end + 1);
  }
  Item(std::string Path) : path(Path) {}
  Item() {
    fileType = "common";
    isHide = false;
    isExecutable = false;
    if (path.size() != 0)
      path = ".";
  }
  virtual ~Item() {}
  virtual const std::string getType() const = 0;
  void printSelf() {
    std::cout.setf(std::ios_base::left);
    std::cout << getName()<<"\t";
  }
  virtual bool isDecoratedByColor() { return decoratedByColor; }
  virtual bool isDecoratedByIcon() { return decoratedByIcon; }
};
/// 装饰器,用来装饰图标或颜色
class FileDecorator : public Item {
protected:
  std::shared_ptr<Item> item;

public:
  explicit FileDecorator(Item *item) : item(item){};
  bool isDecoratedByColor() override { return item->isDecoratedByColor(); }
  bool isDecoratedByIcon() override { return item->isDecoratedByIcon(); }
  virtual const std::string getName() const override = 0;
  const std::string getType() const override { return item->getType(); }
  virtual ~FileDecorator() {}
};
/// 图标类装饰器基类
class IconDecorator : public FileDecorator {
public:
  explicit IconDecorator(Item *item) : FileDecorator(item) {
    item->decoratedByIcon = true;
  }
  virtual const std::string getName() const override = 0;
  virtual ~IconDecorator() {}
};
/// 颜色类装饰器基类
class ColorDecorator : public FileDecorator {
public:
  explicit ColorDecorator(Item *item) : FileDecorator(item) {
    item->decoratedByColor = true;
  }
  virtual const std::string getName() const override = 0;
  virtual ~ColorDecorator() {}
};
/// 具体的各种装饰
//============================================================
/// 普通文件图标装饰
class CommonIcon : public IconDecorator {
public:
  explicit CommonIcon(Item *item) : IconDecorator(item) {}
  const std::string getName() const override {
    return WrapConfig::Icon::common + item->getName();
  }
};
/// 文件夹图标装饰
class DirectoryIcon : public IconDecorator {
public:
  explicit DirectoryIcon(Item *item) : IconDecorator(item) {}
  const std::string getName() const override {
    return WrapConfig::Icon::folder + item->getName();
  }
};

/// 蓝色包裹装饰
class BlueWrap : public ColorDecorator {
public:
  explicit BlueWrap(Item *item) : ColorDecorator(item) {}
  const std::string getName() const override {
    return "\033[34m" + item->getName() + "\033[0m";
  }
};
/// 各种文件类型
//============================================================
/// 文件类型
class FileItem : public Item {
public:
  explicit FileItem(const std::string Path) : Item(Path) {}
  const std::string getType() const override;
};

const std::string FileItem::getType() const { return "File"; }

/// 目录类型
class Directory : public Item {
public:
  explicit Directory(const std::string Path);
  const std::string getType() const override;
};

Directory::Directory(const std::string Path) {
  if (std::filesystem::is_directory(Path)) {
    this->path = Path;
  } else {
    throw DirectoryErr("目标不是一个目录");
  }
}
const std::string Directory::getType() const { return "Directory"; }
/// 文本类型
class TextFile : public Item {
public:
  explicit TextFile(const std::string Path) : Item(Path) {}
  const std::string getType() const override { return "Text"; }
};
/// Cpp类型

/// 文件工厂
//============================================================
/// 根据文件权限以及后缀不同创建不同的文件对象
class FileFactory {
public:
  static Item *getItem(const std::string filePath);
};
Item *FileFactory::getItem(const std::string filePath) {
  FileItem tempItem(filePath);
  Item *item;
  auto fileName = tempItem.getName();
  // 判断目标是否为一个目录
  return item;
}

class FileOperator {
public:
  using LSRES = std::shared_ptr<std::vector<std::shared_ptr<Item>>>;
  static LSRES Ls(const Directory &dir);
  static void showLsRes(LSRES lsRes);
};

FileOperator::LSRES FileOperator::Ls(const Directory &dir) {
  std::filesystem::directory_iterator iter(dir.getPath());
  auto lsRes = std::make_shared<std::vector<std::shared_ptr<Item>>>();
  for (auto &it : iter) {
    if (it.is_directory()) {
      // 路径需要蓝色加路径图标进行装饰
      lsRes->push_back(std::make_shared<BlueWrap>(
          new DirectoryIcon(new Directory(it.path().string()))));
    } else {
      lsRes->push_back(
          std::make_shared<CommonIcon>(new FileItem(it.path().string())));
    }
  }
  return lsRes;
}

void FileOperator::showLsRes(FileOperator::LSRES lsRes) {
  std::cout << "\n";
  for (auto &item : *lsRes) {
    item->printSelf();
  }
  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  std::string path{};
  if (argc == 1) {
    path = ".";
  } else if (argc == 2) {
    path = argv[1];
  } else {
    std::cout << "用法：\n"
              << "\t" << argv[0] << "[path]" << std::endl;
    return -1;
  }

  FileOperator::LSRES lsRes;
  std::unique_ptr<Directory> dir;
  try {
    dir = std::make_unique<Directory>(path);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return -1;
  }
  lsRes = FileOperator::Ls(*dir);
  FileOperator::showLsRes(lsRes);
}
