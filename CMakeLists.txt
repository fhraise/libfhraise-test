cmake_minimum_required(VERSION 3.28)
project(libfhraise_test)

set(CMAKE_CXX_STANDARD 23)

add_executable(libfhraise_test main.cpp)
target_link_libraries(libfhraise_test ${CMAKE_SOURCE_DIR}/libfhraisepy.dll)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
