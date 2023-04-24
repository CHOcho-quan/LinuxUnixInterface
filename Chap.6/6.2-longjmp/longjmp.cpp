/**
 * Check executable file size with a big data segment
 */

#include <fcntl.h>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <setjmp.h>
#include <iostream>
#include <sys/stat.h>

#include "sys_helper.hpp"

static jmp_buf env;

void setJumpPoint() {
  if (setjmp(env) == 0) printf("I'm the first time!\n");
  else printf("I'm here because of longjmp!\n");
}

int main(int argc, char* argv[]) {
  setJumpPoint();
  // You'll get a core dump here
  longjmp(env, 3);
  return 0;
}
