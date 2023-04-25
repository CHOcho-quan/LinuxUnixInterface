/**
 * Check if sbrk change program break during malloc
 */

#include <fcntl.h>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <sys/stat.h>

#include "sys_helper.hpp"

#define MAX_ALLOCS 1000000

int main(int argc, char* argv[]) {
  /**
   * @brief check if sbrk change program break during malloc
   */
  char *ptr[MAX_ALLOCS];
  int freeStep, freeMin, freeMax, blockSize, numAllocs, j;

  printf("\n");

  if (argc < 3 || strcmp(argv[1], "help") == 0) {
    printf("%s num-allocs block-size [step [min [max]]]\n", argv[0]);
    exit(1);
  }

  numAllocs = getInt(argv[1])
}
