cmake_minimum_required(VERSION 3.14)
project(fmt_demo CXX)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/.. fmt_build)

add_executable(fmt_demo main.cpp)
target_link_libraries(fmt_demo PRIVATE fmt::fmt)
target_compile_features(fmt_demo PRIVATE cxx_std_17)
