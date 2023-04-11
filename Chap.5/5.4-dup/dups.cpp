/**
 * Open a file using O_APPEND and set SEEK to see where it's gonna write
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>

#include "file_helper.hpp"

int dup(int fd) {
  int new_fd = fcntl(fd, F_DUPFD);
  if (new_fd < 0) {
    std::cerr << "Runtime Error: Duplicate fd failed\n";
    return -1;
  }
  return new_fd;
}

int dup2(int old_fd, int new_fd) {
  if (old_fd == new_fd) {
    CHECK_FILE_OP_STATUS(fcntl(old_fd, F_GETFL, 0));
    return new_fd;
  }
  CHECK_FILE_OP_STATUS(close(new_fd));
  CHECK_FILE_OP_STATUS(fcntl(old_fd, F_DUPFD, new_fd));
  return new_fd;
}
