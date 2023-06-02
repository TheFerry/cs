cmake_minimum_required(VERSION 3.1)
project(cs)

option(BUILD_TEST "BUILD TEST" OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++11" SUPPORT_CXX11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(${SUPPORT_CXX11})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
  message(FATAL_ERROR "compiler dosen't support cpp11")
endif()

aux_source_directory(src/core CORESRC)
aux_source_directory(src/assets ASSETSSRC)
aux_source_directory(src/file FILESRC)

set(LIBSRC ${CORESRC} ${ASSETSSRC} ${FILESRC})
set(INCLUDES src/assets src/core src/file)
set(SRC src/cmd/run.cpp)

add_library(cs-core ${LIBSRC})
target_include_directories(cs-core PUBLIC ${INCLUDES})

if(BUILD_TEST)
  add_executable(test test/test.cpp)
  target_link_libraries(test PRIVATE cs-core)
endif()

add_executable(cs ${SRC})
target_link_libraries(cs PRIVATE cs-core)


install(TARGETS cs RUNTIME DESTINATION bin)
