#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_1_action(void *data) {
  int i;
  for (i = 0; i < 10; i++) {
    sleep(1);
    printf("Thread '%ld' - Got %d\n", (intptr_t)data, i);
  }

  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t thread_1;
  int thr_id, a = 1, b = 2;

  thr_id =
      pthread_create(&thread_1, NULL, thread_1_action, (void *)(intptr_t)a);
  thread_1_action((void *)(intptr_t)b);

  return EXIT_SUCCESS;
}
