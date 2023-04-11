/**
 * Open a file using O_APPEND and set SEEK to see where it's gonna write
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>

#include "file_helper.hpp"

int main(int argc, char* argv[]) {
  /**
   * @brief input an existing file we'll open it as O_APPEND
   * and set SEEK at start then try to write the file
   * @param input_file an existing file to write
   */
  if (argc < 2) {
    std::cerr << "Invalid Argument: Filepath Unknown\n";
    exit(1);
  }

  auto input_file = argv[1];
  int fd = open(input_file, O_RDWR | O_APPEND);
  if (fd < 0) {
    std::cerr << "Runtime Error: File not exists\n";
    exit(1);
  }

  // set seek at the start
  CHECK_FILE_OP_STATUS(lseek(fd, 0, SEEK_SET))

  // write some random buff -> still gonna write at the end
  char* buff = "quan";
  CHECK_FILE_OP_STATUS(write(fd, buff, 4 * sizeof(char)))

  CHECK_FILE_OP_STATUS(close(fd))
}
