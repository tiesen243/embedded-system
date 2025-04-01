#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

int pwm_fd, buttons_fd;
static int freq = 500;

void sleep_ms(int ms) { usleep(ms * 1000); }
void set_buzzer_freq(int fd, int freq);

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

  while (1) {
    set_buzzer_freq(pwm_fd, freq);
    sleep(1);

    freq += 100;
    if (freq > 3000)
      freq = 500;
    printf("Current freq = %dHz", freq);
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
      freq += 100;
      if (freq >= 3000)
        freq = 3000;
      printf("K1 is pressed/released, freq = %dHz\n", freq);
    }

    if (curr_btn[1] != prev_btn[1]) {
      sleep_ms(300);
      prev_btn[1] = curr_btn[1];
      freq -= 100;
      if (freq <= 100)
        freq = 100;
      printf("K2 is pressed/released, freq = %dHz\n", freq);
    }
  }

  pthread_exit(NULL);
}

void set_buzzer_freq(int fd, int freq) {
  int ret = ioctl(fd, 1, freq);
  if (ret < 0) {
    perror("set the frequency of the buzzer");
    exit(1);
  }
}
