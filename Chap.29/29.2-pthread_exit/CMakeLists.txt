cmake_minimum_required(VERSION 3.10)

add_executable(pthread_exit pthread_exit.cpp)
target_link_libraries(pthread_exit pthread)
