project(cs)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 指定为 C++17 版本
set(CMAKE_CXX_STANDARD 17)
set(SRC 
  src/core/arranger.cpp 
  src/core/flags.cpp 
  src/core/run.cpp
  src/file/file.cpp)
set(HEADERS
    src/assets/iconDirs.h
    src/assets/iconExtension.h
    src/assets/iconFilename.h
    src/assets/icons.h
    src/file/file.h
    src/core/arranger.h
    src/core/cxxopts.hpp
    src/core/logger.h
    src/core/flags.h)

add_executable(${PROJECT_NAME} ${SRC} ${HEADERS})

install(TARGETS ${PROJECT_NAME})
