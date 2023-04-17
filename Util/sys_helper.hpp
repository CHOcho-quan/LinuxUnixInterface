#pragma once

#include <cstring>
#include <limits.h>
#include <iostream>

/**
 * Check a system operation function is doing well
 */
#define CHECK_SYS_OP_STATUS(func)              \
  if ((func) < 0) {                             \
    std::cerr << "Runtime Error due to "        \
             << strerror(errno) << '\n';        \
    exit(1);                                    \
  }

/**
 * Helper to get number from opt arg
 */
#define GN_NONNEG 01 // non-negative
#define GN_GT_0   02 // positive

#define GN_ANY_BASE 0100 // use any base
#define GN_BASE_8   0200 // oct number
#define GN_BASE_16  0400 // hex number

static long getNum(const char* fname, const char *arg, int flags, const char* name) {
  long res;
  char* endptr;
  int base;

  if (arg == NULL || *arg == '\0') {
    printf("Invalid argument\n");
    exit(1);
  }

  base = (flags & GN_ANY_BASE) ? 0 : (flags & GN_BASE_8) ? 8 : (flags & GN_BASE_16) ? 16 : 10;

  errno = 0;
  res = strtol(arg, &endptr, base);
  if (errno != 0) {
    printf("strtol failed to convert to long\n");
    exit(1);
  }

  if (*endptr != '\0') {
    printf("Nonnumeric characters to convert\n");
    exit(1);
  }

  if ((flags & GN_NONNEG) && res < 0) {
    printf("Negative value not allowed\n");
    exit(1);
  }

  if ((flags & GN_GT_0) && res <= 0) {
    printf("Non-positive value not allowed\n");
    exit(1);
  }

  return res;
}

inline long getLong(const char* arg, int flags, const char* name) {
  return getNum("getLong", arg, flags, name);
}

inline int getInt(const char* arg, int flags, const char* name) {
  long res = getNum("getInt", arg, flags, name);

  if (res > INT_MAX || res < INT_MIN) {
    printf("Number is beyond integer, please use long\n");
    exit(1);
  }

  return (int) res;
}
