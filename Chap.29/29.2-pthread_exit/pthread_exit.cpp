/**
 * Check self joined pthread behavior
 */

#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <sys/stat.h>

#include "sys_helper.hpp"

struct boring {
  int a;
};

static void* threadFunc(void* arg) {
  sleep(1);
  // this might be destructed! though it might not be observable here
  struct boring* boredthr = (struct boring*) arg;
  printf("Message from some thread %ld with %d\n", (long)pthread_self(), boredthr->a);
}

int main(int argc, char** argv) {
  printf("Message from Main thread\n");
  struct boring bored;
  bored.a = 10;

  pthread_t thr;
  CHECK_SYS_OP_STATUS(pthread_create(&thr, nullptr, threadFunc, (void*)&bored));
  printf("Everything in main thread finished\n");
  pthread_exit(nullptr);
}