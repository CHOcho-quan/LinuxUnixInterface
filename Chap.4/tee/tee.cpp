#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>

extern int optind,opterr,optopt;
extern char *optarg;

enum {
  TEE_NORMAL,
  TEE_APPEND
};

int main(int argc, char* argv[]) {
  int c = 0, mode = TEE_NORMAL, fd = -1;
  while (EOF != (c = getopt(argc, argv, "a"))) {
    switch(c) {
      case 'a':
        mode = TEE_APPEND;
      default:
        break;
    }    
  }

  if (argc < 1 + optind) {
    std::cerr << "Invalid Argument: Filepath Unknown\n";
    exit(1);
  }
  
  auto output_path = argv[optind];
  switch (mode) {
    case TEE_NORMAL:
      fd = open(output_path, O_RDWR | O_TRUNC | O_CREAT, 0777);
      break;
    case TEE_APPEND:
      fd = open(output_path, O_RDWR | O_APPEND | O_CREAT, 0777);
  }
  std::cout << fd;

  if (fd < 0) {
    std::cerr << "Runtime Error: Failed to Open File\n";
    exit(1);
  }

  // Now read terminal for output
  char buff;
  while (read(STDIN_FILENO, &buff, 1) > 0) {
    if (write(fd, &buff, 1) < 0) {
      std::cerr << "Runtime Error: Failed to Write to File\n";
      exit(1);
    }
  }

  if (close(fd) < 0) std::cerr << "Runtime Error: Failed to Close File\n";
  exit(0);
}
