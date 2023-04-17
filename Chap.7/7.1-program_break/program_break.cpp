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
}
