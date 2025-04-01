#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

int leds_fd, buttons_fd;
static int db = 1000;

void sleep_ms(int ms) { usleep(ms * 1000); }

void *btn_polling(void *param);

int main(int argc, char *argv[]) {
  const char *thread_params = "Button thread";
  pthread_t thread_1;

  leds_fd = open("/dev/pwm", O_RDONLY);
  if (leds_fd < 0) {
    perror("open buzzer");
    return EXIT_FAILURE;
  }

  buttons_fd = open("/dev/buttons", O_RDONLY);
  if (buttons_fd < 0) {
    perror("open buttons");
    return EXIT_FAILURE;
  }

  thread_1 =
      pthread_create(&thread_1, NULL, btn_polling, (void *)thread_params);

  while (1) {
    int ret = ioctl(leds_fd, 1, db);
    if (ret < 0) {
      perror("set the frequency of the buzzer");
      return EXIT_FAILURE;
    }
  }

  close(buttons_fd);
  close(leds_fd);

  return EXIT_SUCCESS;
}

void *btn_polling(void *param) {
  int i, curr_btn[2], prev_btn[2] = {0, 0};

  for (;;) {
    int num = read(buttons_fd, curr_btn, sizeof(curr_btn));
    if (num != sizeof(curr_btn)) {
      perror("read buttons");
      pthread_exit(NULL);
    }

    if (curr_btn[0] != prev_btn[0]) {
      sleep_ms(300);
      prev_btn[0] = curr_btn[0];
      if (db < 3000)
        db += 50;
      printf("K1 is pressed, dB = %d\n", db);
    }

    if (curr_btn[1] != prev_btn[1]) {
      sleep_ms(300);
      prev_btn[1] = curr_btn[1];
      if (db > 0)
        db -= 50;
      printf("K2 is pressed, dB = %d\n", db);
    }
  }

  pthread_exit(NULL);
}
