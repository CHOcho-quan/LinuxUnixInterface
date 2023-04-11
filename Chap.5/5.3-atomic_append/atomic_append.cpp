/**
 * Try to append a file w/wo using O_APPEND
 */

#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>

#include "file_helper.hpp"

enum {
  APPEND_IT,
  NO_APPEND
};

int main(int argc, char* argv[]) {
  /**
   * @brief example usage ./atomic_append filename num-bytes [x]
   * we'll write num-bytes data into filename w/wo O_APPEND depending by x parameter
   * @param filename indicates the path filename
   * @param num_bytes indicates the size of writing data
   * @param x if x is specified, we're not going to use O_APPEND
   */
  int fd = -1, mode, num_bytes = 0;
  if (argc < 3) {
    std::cerr << "Invalid Argument: Filepath Unknown\n";
    exit(1);
  }

  mode = argc == 3 ? APPEND_IT : NO_APPEND;
  num_bytes = std::atoi(argv[2]);
  char buff = 'q';
  if (mode == NO_APPEND) { // non-atomic file appending
    fd = open(argv[1], O_RDWR | O_CREAT, 0666);
  } else {
    fd = open(argv[1], O_RDWR | O_CREAT | O_APPEND, 0666);
  }

  CHECK_FILE_OP_STATUS(fd);
  for (int i = 0; i < num_bytes; ++i) {
    if (mode == NO_APPEND) CHECK_FILE_OP_STATUS(lseek(fd, 0, SEEK_END));
    CHECK_FILE_OP_STATUS(write(fd, &buff, sizeof(char)));
  }

  CHECK_FILE_OP_STATUS(close(fd));
}
