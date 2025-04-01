#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

int pwm_fd, buttons_fd;
static int freq = 1000;

void sleep_ms(int ms) { usleep(ms * 1000); }

void *btn_polling(void *param);

int main(int argc, char *argv[]) {
  pwm_fd = open("/dev/pwm", O_RDONLY);
  if (pwm_fd < 0) {
    perror("open pwm");
    exit(EXIT_FAILURE);
  }

  buttons_fd = open("/dev/buttons", O_RDONLY);
  if (buttons_fd < 0) {
    perror("open buttons");
    exit(EXIT_FAILURE);
  }

  pthread_t t = pthread_create(&t, NULL, btn_polling, (void *)"Button thread");

  for (int idx = 0; idx < 4; idx++)
    ioctl(pwm_fd, 0, idx);

  while (1) {
    for (int idx = 0; idx < 4; idx++) {
      ioctl(pwm_fd, 1, idx);
      sleep_ms(freq);
      ioctl(pwm_fd, 0, idx);
    }
  }

  close(buttons_fd);
  close(pwm_fd);

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
      sleep_ms(300);
      prev_btn[0] = curr_btn[0];
      freq += 50;
      printf("K1 is pressed/released, time_ms = %dms\n", freq);
    }

    if (curr_btn[1] != prev_btn[1]) {
      sleep_ms(300);
      prev_btn[1] = curr_btn[1];
      freq -= 50;
      if (freq < 100)
        freq = 100;
      printf("K2 is pressed/released, time_ms = %dms\n", freq);
    }
  }

  pthread_exit(NULL);
}
