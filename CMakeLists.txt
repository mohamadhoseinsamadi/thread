cmake_minimum_required(VERSION 3.16)
project(thread C)

set(CMAKE_C_STANDARD 11)

find_package(Threads REQUIRED)

add_executable(thread main.c)
target_link_libraries(thread PRIVATE Threads::Threads)