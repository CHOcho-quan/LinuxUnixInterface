cmake_minimum_required(VERSION 3.10)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Util/)

add_subdirectory(5.1-create_lf)
add_subdirectory(5.2-append_test)
add_subdirectory(5.3-atomic_append)
add_subdirectory(5.4-dup)
add_subdirectory(5.5-verify_fd)
add_subdirectory(5.7-readv_writev)