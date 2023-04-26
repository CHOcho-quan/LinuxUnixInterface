#include <pthread.h>

#include "sys_helper.hpp"

static int glob = 0; /* loop arg time incrementing glob */

static void* threadFunc(void* arg) {
  int loops = *((int *) arg);
  int loc, j;

  for (j = 0; j < loops; ++j) {
    printf("%ld thread in loop %d with current glob value %d\n", (long)pthread_self(), j, glob);
    loc = glob;
    loc++;
    glob = loc;
  }

  return nullptr;
}

int main(int argc, char* argv[]) {
  pthread_t t1, t2;
  int loops;
  loops = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-loops") : 10000000;

  CHECK_SYS_OP_STATUS(pthread_create(&t1, nullptr, threadFunc, &loops));
  CHECK_SYS_OP_STATUS(pthread_create(&t2, nullptr, threadFunc, &loops));
  
  CHECK_SYS_OP_STATUS(pthread_join(t1, nullptr));
  CHECK_SYS_OP_STATUS(pthread_join(t2, nullptr));

  printf("glob = %d\n", glob);
  exit(0);
}
