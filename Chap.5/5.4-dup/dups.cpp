/**
 * Open a file using O_APPEND and set SEEK to see where it's gonna write
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>

#include "file_helper.hpp"

extern int optind,opterr,optopt;
extern char *optarg;

int dup(int fd) {
  int new_fd = fcntl(fd, F_DUPFD, 0);
  if (new_fd < 0) {
    std::cerr << "Runtime Error: Duplicate fd failed\n";
    return -1;
  }
  return new_fd;
}

int dup2(int old_fd, int new_fd) {
  if (old_fd == new_fd) {
    CHECK_FILE_OP_STATUS(fcntl(old_fd, F_GETFL));
    return new_fd;
  }
  close(new_fd); // need not to check because it may not be opened
  CHECK_FILE_OP_STATUS(fcntl(old_fd, F_DUPFD, new_fd));
  return new_fd;
}

int main(int argc, char* argv[]) {
  /**
   * @brief input a file and we'll open it and duplicate it
   * @param filename indicates the path filename
   */
  int fd = -1, new_fd = 109;
  if (argc < 2) {
    std::cerr << "Invalid Argument: Filepath Unknown\n";
    exit(1);
  }

  char* filepath = argv[optind];
  const char* buff = "CHECK BUFF\n";
  fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, 0666);
  int dup_fd = dup(fd);
  CHECK_FILE_OP_STATUS(write(dup_fd, buff, 11 * sizeof(char)));
  dup2(fd, new_fd);
  CHECK_FILE_OP_STATUS(write(new_fd, buff, 11 * sizeof(char)));
  CHECK_FILE_OP_STATUS(close(fd));
  CHECK_FILE_OP_STATUS(close(new_fd));
}
