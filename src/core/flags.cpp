#include "flags.h"
#include <cstdlib>
#include <memory>
#include <iostream>
core::Flags::Flags(int argc, char *argv[]) {
  options.reset(new cxxopts::Options("cs", "a modern ls command"));
  options->add_options()("a,all", "list all files")("i,icon", "hidden icons")(
      "l,long", "list detail infomation")("c,color", "disable color")(
      "h,help", "display help");
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
  } catch (cxxopts::exceptions::no_such_option &e) {
    std::cout<<core::helpInfo<<std::endl;
    exit(EXIT_SUCCESS);
  }
}
core::Flags &core::Flags::getInstance(int argc, char *argv[]) {
  static Flags instance(argc, argv);
  return instance;
}
