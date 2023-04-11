/**
 * Try using off64_t to create a big file
 */

#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>

#include "file_helper.hpp"

#ifdef _FILE_OFFSET_BITS
  #define OFF_T off64_t
  #define OPEN open64
  #define LSEEK lseek64
#else // _FILE_OFFSET_BITS
  #define OFF_T off_t
  #define OPEN open
  #define LSEEK lseek
#endif // _FILE_OFFSET_BITS

int main(int argc, char* argv[]) {
  int fd;
  OFF_T off;
  if (argc != 3) {
    std::cerr << "Invalid Argument\n";
    exit(1);
  }

  fd = OPEN(argv[1], O_RDWR | O_CREAT, 0666);
  if (fd == -1) {
    std::cerr << "Runtime Error: Failed to open file\n";
    exit(1);
  }

  off = atoll(argv[2]);
  CHECK_FILE_OP_STATUS(LSEEK(fd, off, SEEK_SET))

  CHECK_FILE_OP_STATUS(write(fd, "test", 4))

  CHECK_FILE_OP_STATUS(close(fd));
  exit(0);
}
