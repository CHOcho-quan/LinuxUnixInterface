cmake_minimum_required(VERSION 3.10)

add_executable(thread_safe_tree thread_safe_tree.cpp)
target_link_libraries(thread_safe_tree pthread)
