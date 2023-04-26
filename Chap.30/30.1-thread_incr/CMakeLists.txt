cmake_minimum_required(VERSION 3.10)

add_executable(thread_incr thread_incr.cpp)
target_link_libraries(thread_incr pthread)
