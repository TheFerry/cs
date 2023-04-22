cmake_minimum_required(VERSION 3.15)
project(cs)

option(BUILD_TEST "BUILD TEST" on)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD TRUE)
set(CMAKE_CXX_STANDARD 11)

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
