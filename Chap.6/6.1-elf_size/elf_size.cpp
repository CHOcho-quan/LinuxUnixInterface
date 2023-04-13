/**
 * Check executable file size with a big data segment
 */

#include <fcntl.h>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <sys/stat.h>

#include "sys_helper.hpp"

char globBuf[65536];
int primes[] = { 2, 3, 5, 7 };

static int square(int x) {
  int result;
  result = x * x;
  return result;
}

static void doCalc(int val) {
  printf("The square of %d is %d\n", val, square(val));

  if (val < 1000) {
    int t;

    t = val * val * val;
    printf("The cube of %d is %d\n", val, t);
  }
}

int main(int argc, char* argv[]) {
  /**
   * @brief check if the executable of a program with big data segment
   * will be big as it indicates or not
   */
  static int key = 9973;
  static char mbuf[1024000];
  char *p;

  p = (char *) malloc(1024);
  
  doCalc(key);

  free(p);
  exit(0);
}
