#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

static void* thread_func(void* param) {

  char* arg = (char*) param;
  if(!strcmp(arg, "sensor")) {
      execvp("readData.py", NULL);
  }

}

int main() {




}
