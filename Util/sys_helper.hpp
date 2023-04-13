#pragma once

#include <cstring>
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
