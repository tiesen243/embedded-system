#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char message[] = "Hello world";

void *thread_1_action(void *data) {
  printf("Thread fuction is executing...\n");

  printf("Thread data is '%s'\n", (char *)message);
  sleep(3);
  strcpy(message, "Bye");

  pthread_exit("Thank you!");
}

int main(int argc, char *argv[]) {
  pthread_t thread_1;
  int res;
  void *thread_result;

  res = pthread_create(&thread_1, NULL, thread_1_action, (void *)message);

  if (res != 0) {
    perror("Thread create error");
    exit(EXIT_FAILURE);
  }

  printf("Waiting for thread to finish...\n");
  res = pthread_join(thread_1, &thread_result);
  if (res != 0) {
    perror("Thread wait error");
    exit(EXIT_FAILURE);
  }

  printf("Thread complete and return '%s'\n", (char *)thread_result);
  printf("Message: '%s'\n", message);

  return EXIT_SUCCESS;
}
