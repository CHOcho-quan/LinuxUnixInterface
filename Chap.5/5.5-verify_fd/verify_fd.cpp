/**
 * Verify if copies of fd share offset & flag
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>

#include "sys_helper.hpp"

int main(int argc, char* argv[]) {
  /**
   * @brief open a file and duplicate it. Then we'll check if the two fd
   * share the same offset & flag
   */
  int fd = open("./check.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
  int dup_fd = dup(fd);
  if (fcntl(fd, F_GETFL) != fcntl(dup_fd, F_GETFL)) {
    std::cerr << "Really? Duplicated fd doesn't share Flags!\n";
    return -1;
  }

  // Move seek offset by one file
  CHECK_SYS_OP_STATUS(lseek(fd, 1, SEEK_CUR));
  if (lseek(fd, 0, SEEK_CUR) != lseek(dup_fd, 0, SEEK_CUR)) {
    std::cerr << "Really? Duplicated fd doesn't share Offset!\n";
    return -1;
  }

  // a simple check for Q5.6
  // int fd1 = open("./check2.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
  // int fd2 = dup(fd1);
  // int fd3 = open("./check2.txt", O_RDWR, 0666);
  // write(fd1, "Hello,", 6);
  // write(fd2, "worldd", 6);
  // lseek(fd2, 0, SEEK_SET);
  // write(fd1, "HELLO,", 6);
  // write(fd3, "Gidday,", 6);

  CHECK_SYS_OP_STATUS(close(fd));

  std::cout << "Duplicated fd share offset & flags\n";
  return 0;
}
