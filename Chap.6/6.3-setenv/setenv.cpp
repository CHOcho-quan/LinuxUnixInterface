/**
 * Implement setenv & unsetenv by putenv & getenv
 */

#include <string>
#include <fcntl.h>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <sys/stat.h>

#include "sys_helper.hpp"

int setenv(const char* name, const char* value, int overwrite) {
  auto cur_env = getenv(name);
  if (cur_env != NULL && overwrite == 0) return -1;

  std::string str_name = name, str_val = value, n2v = str_name + "=" + str_val;
  char* buff = (char*) malloc(n2v.length() + 1);
  buff[n2v.length()] = '\0';
  memcpy(buff, &n2v[0], n2v.length() * sizeof(char));

  CHECK_SYS_OP_STATUS(putenv(buff));
}

int unsetenv(const char* name) {
  char* old_value = getenv(name);
  char* env = (char*) calloc(1024, 0);
  if(old_value == NULL) return -1;
  memcpy(env, name, strlen(name));
  strcat(env,"=");
  strcat(env,old_value);
  char ** newenv = (char**) calloc(1024 * sizeof(char **), 0);
  int i = 0;
  for(char **ep = environ; *ep != NULL;ep++){
      if(strcmp(env, *ep) != 0){ // remove that env
          newenv[i++] = *ep;
      }
      else{
          printf("clear env %s\n", *ep);
      }
  }
  free(environ);
  environ = newenv;
  return 0;
}

void printenv(){
  printf("The envs are:\n");
  char **ep;
  for(ep = environ; *ep != NULL; ep++)
    puts(*ep);
}

int main(int argc, char* argv[]) {
  clearenv();
  putenv("CHECK=999");
  putenv("abcdefg=84uij");
  // we don't overwrite at the first time
  setenv("abcdefg", "hijklmn", 0);
  printenv();
  // overwrite the 84uij
  setenv("abcdefg", "1234567", 1);
  printenv();
  unsetenv("abcdefg");
  printenv();

  return 0;
}
