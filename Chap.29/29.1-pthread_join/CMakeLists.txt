cmake_minimum_required(VERSION 3.10)

add_executable(pthread_join pthread_join.cpp)
target_link_libraries(pthread_join pthread)
