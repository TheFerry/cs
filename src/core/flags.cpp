#include "flags.h"
#include <cstdlib>
#include <iostream>
#include <memory>
core::Flags::Flags(int argc, char *argv[]) {
  options.reset(new cxxopts::Options("cs", "a modern ls command"));
  options->add_options()
    ("a,all", "list all files")
    ("i,icon", "hidden icons")
    ("l,long", "list detail infomation")
    ("c,color", "disable color")
    ("h,help", "display help")
    ("r,reverse", "reverse order")
    ("t,time", "order by modified time")
    ("d,directory", "only list directories")
    ("A,All", "the same to all,but don't show . and ..")
    ("R,recursion","Recursively displays files and subdirectories in the file");
  m_flag = 0;
  try {
    auto result = options->parse(argc, argv);
    if (result.count("all")) {
      m_flag |= flag_a;
    }
    if (result.count("long")) {
      m_flag |= flag_l;
    }
    if (result.count("color")) {
      m_flag |= flag_c;
    }
    if (result.count("help")) {
      m_flag |= flag_h;
    }
    if (result.count("icon")) {
      m_flag |= flag_i;
    }
    if (result.count("reverse")) {
      m_flag |= flag_r;
    }
    if (result.count("time")) {
      m_flag |= flag_t;
    }
    if (result.count("All")) {
      m_flag |= flag_A;
    }
    if (result.count("recursion")) {
      m_flag |= flag_R;
    }
    if (result.count("directory")) {
      m_flag |= flag_d;
    }
  } catch (cxxopts::exceptions::no_such_option &e) {
    std::cout << core::helpInfo << std::endl;
    exit(EXIT_SUCCESS);
  }
}
core::Flags &core::Flags::getInstance(int argc, char *argv[]) {
  static Flags instance(argc, argv);
  return instance;
}
