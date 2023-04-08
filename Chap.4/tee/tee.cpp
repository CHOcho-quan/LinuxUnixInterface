/**
 * Reproduce a simple version of built-in linux command `tee`
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>

extern int optind,opterr,optopt;
extern char *optarg;

/**
 * @enum indicating the tee mode parameter
 */
enum {
  TEE_NORMAL, // Truncated mode for tee
  TEE_APPEND  // Appending mode for tee
};

int main(int argc, char* argv[]) {
  /**
   * @brief input an output path and input any string on terminal
   * the results will be redirected to the output path file
   * @param output_path indicates the output path filename
   * @note use -a choice for append mode
   */
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

  // close file
  if (close(fd) < 0) {
    std::cerr << "Runtime Error: Failed to Close File\n";
    exit(1);
  }
  exit(0);
}
