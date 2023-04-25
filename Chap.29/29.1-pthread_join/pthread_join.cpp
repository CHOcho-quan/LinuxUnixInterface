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

static void* threadFunc(void* arg) {
  printf("Message from some thread %ld\n", (long)pthread_self());
  pthread_join(pthread_self(), nullptr); // undefined behavior, sometimes the thread ran twices
}

int main(int argc, char** argv) {
  printf("Message from Main thread\n");
  pthread_t thr;
  CHECK_SYS_OP_STATUS(pthread_create(&thr, nullptr, threadFunc, (void*)"Hello world\n"));
  printf("Everything in main thread finished\n");
}