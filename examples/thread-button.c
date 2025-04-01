#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

int leds_fd, buttons_fd;
static int time_ms = 1000;

void *btn_polling(void *param);

int main(int argc, char *argv[]) {
  leds_fd = open("/dev/leds", O_RDONLY);
  if (leds_fd < 0) {
    perror("open leds");
    exit(EXIT_FAILURE);
  }

  buttons_fd = open("/dev/buttons", O_RDONLY);
  if (buttons_fd < 0) {
    perror("open buttons");
    exit(EXIT_FAILURE);
  }

  pthread_t t = pthread_create(&t, NULL, btn_polling, (void *)"Button thread");

  for (int idx = 0; idx < 4; idx++)
    ioctl(leds_fd, 0, idx);

  while (1) {
    for (int idx = 0; idx < 4; idx++) {
      ioctl(leds_fd, 1, idx);
      usleep(time_ms * 1000);
      ioctl(leds_fd, 0, idx);
    }
  }

  close(buttons_fd);
  close(leds_fd);

  return EXIT_SUCCESS;
}

void *btn_polling(void *param) {
  int curr_btn[2], prev_btn[2] = {0, 0};

  while (1) {
    int num = read(buttons_fd, curr_btn, sizeof(curr_btn));
    if (num != sizeof(curr_btn)) {
      perror("read buttons");
      exit(EXIT_FAILURE);
    }

    if (curr_btn[0] != prev_btn[0]) {
      usleep(300 * 1000);
      prev_btn[0] = curr_btn[0];
      time_ms += 50;
      printf("K1 is pressed/released, time_ms = %dms\n", time_ms);
    }

    if (curr_btn[1] != prev_btn[1]) {
      usleep(300 * 1000);
      prev_btn[1] = curr_btn[1];
      time_ms -= 50;
      if (time_ms < 100)
        time_ms = 100;
      printf("K2 is pressed/released, time_ms = %dms\n", time_ms);
    }
  }

  pthread_exit(NULL);
}
