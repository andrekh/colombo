cmake_minimum_required(VERSION 3.17)
project(colombo)

set(CMAKE_CXX_STANDARD 14)


add_executable(colombo main.cpp utils.cpp utils.h vanillaTCP.cpp vanillaTCP.h)

find_package(Threads REQUIRED)
target_link_libraries(colombo PRIVATE Threads::Threads)