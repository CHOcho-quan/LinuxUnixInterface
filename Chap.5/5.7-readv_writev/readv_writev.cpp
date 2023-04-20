/**
 * Implement readv & writev using read & write
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>

#include "sys_helper.hpp"

// This struct is defined under fcntl.h
// struct iovec {
//   void *iov_base;
//   size_t iov_len;
// };

ssize_t readv(int fd, const struct iovec *iov, int iovcnt) {
  ssize_t readbytes = 0;
  for (int i = 0; i < iovcnt; ++i) {
    auto cur_iov = iov[i];
    auto readbyte = read(fd, cur_iov.iov_base, cur_iov.iov_len);
    CHECK_SYS_OP_STATUS(readbyte);

    readbytes += readbyte;
  }

  return readbytes;
}

ssize_t writev(int fd, const struct iovec* iov, int iovcnt) {
  int buffer_size = 0, cur = 0;
  for (int i = 0; i < iovcnt; ++i) buffer_size += iov[i].iov_len;
  void* buff = malloc(buffer_size);

  for (int i = 0; i < iovcnt; ++i) {
    memcpy(buff + cur, iov[i].iov_base, iov[i].iov_len);
    cur += iov[i].iov_len;
  }

  auto wsize = write(fd, buff, buffer_size);
  CHECK_SYS_OP_STATUS(wsize);
  return wsize;
}

int main(int argc, char* argv[]) {
  /**
   * @brief input a file and read it to buffer and then write the iov to another file
   */
  int fd, x;
  struct iovec iov[2];
  char str[100];

  if (argc != 2) {
    std::cerr << "Need more arguments\n";
    exit(1);
  }

  fd = open(argv[1], O_RDWR);
  CHECK_SYS_OP_STATUS(fd);
  iov[0].iov_base = &x;
  iov[0].iov_len = sizeof(x);

  iov[1].iov_base = &str;
  iov[1].iov_len = 100 * sizeof(char);

  auto numRead = readv(fd, iov, 2);
  CHECK_SYS_OP_STATUS(numRead);

  printf("Readv test: reading %d bytes using readv while 104 bytes provided\n", numRead);

  int writefd = open("./writev_test", O_CREAT | O_RDWR, 0777);
  CHECK_SYS_OP_STATUS(writev(writefd, iov, 2));

  return 0;
}
