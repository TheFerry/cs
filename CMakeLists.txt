cmake_minimum_required(VERSION 3.15)
project(cs)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 17)

aux_source_directory(src/core CORESRC)
aux_source_directory(src/assets ASSETSSRC)
aux_source_directory(src/file FILESRC)

set(LIBSRC ${CORESRC} ${ASSETSSRC} ${FILESRC})
set(INCLUDES src/assets src/core src/file)

set(SRC src/cmd/run.cpp)

add_library(cs-core ${LIBSRC})
target_include_directories(cs-core PUBLIC ${INCLUDES})

add_executable(cs ${SRC})
target_link_libraries(cs PRIVATE cs-core)

install(TARGETS cs RUNTIME DESTINATION bin)
