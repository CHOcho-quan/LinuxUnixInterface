/**
 * Reproduce a simple version of built-in linux command `cp` to a file
 */

#include <string>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

#include "sys_helper.hpp"

int main(int argc, char* argv[]) {
  /**
   * @brief input an filename and output path, the function will
   * copy the given filename to the output path
   * @param input_file indicates the filename to be copied
   * @param output_path indicates the output path filename
   */

  if (argc < 3) {
    std::cerr << "Invalid Arguments: Need input / output file path\n";
    exit(1);
  }

  auto input_file = argv[1], output_path = argv[2];

  // open input file and output file
  int in_fd = open(input_file, O_RDONLY),
      out_fd = open(output_path, O_RDWR | O_TRUNC | O_CREAT, 0666);
  if (in_fd == -1 || out_fd == -1) {
    std::cerr << "Runtime Error: Failed to open files\n";
    exit(1);
  }

  // read input and write to output
  char buff;
  while (read(in_fd, &buff, 1) > 0) {
    // sparse file case on empty string
    if (buff == 0) {
      CHECK_SYS_OP_STATUS(lseek(out_fd, 1, SEEK_CUR))
    }
    CHECK_SYS_OP_STATUS(write(out_fd, &buff, 1))
  }

  // close files
  CHECK_SYS_OP_STATUS(close(in_fd) < 0 || close(out_fd) < 0)

  exit(0);
}