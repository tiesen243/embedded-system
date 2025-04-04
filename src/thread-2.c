#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

int pwm_fd, buttons_fd;
static int freq = 500, time_ms = 1000;

void set_buzzer_freq(int fd, int freq);
void stop_buzzer(int fd);

void *btn_polling(void *param);

int main(int argc, char *argv[]) {
  pwm_fd = open("/dev/pwm", 0);
  if (pwm_fd < 0) {
    perror("open pwm");
    exit(EXIT_FAILURE);
  }

  buttons_fd = open("/dev/buttons", 0);
  if (buttons_fd < 0) {
    perror("open buttons");
    exit(EXIT_FAILURE);
  }

  pthread_t t = pthread_create(&t, NULL, btn_polling, (void *)"Button thread");
  set_buzzer_freq(pwm_fd, freq);

  while (1) {
    usleep(time_ms * 1000);

    freq += 100;
    if (freq > 3000)
      freq = 500;
    printf("Current freq = %dHz\n", freq);
    set_buzzer_freq(pwm_fd, freq);
  }

  usleep(500 * 1000);
  ioctl(pwm_fd, 0);
  close(pwm_fd);

  close(buttons_fd);

  return EXIT_SUCCESS;
}

void *btn_polling(void *param) {
  char curr_btn[3], prev_btn[3] = {'0', '0', '0'};

  while (1) {
    int num = read(buttons_fd, curr_btn, sizeof(curr_btn));
    if (num != sizeof(curr_btn)) {
      perror("read buttons");
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 3; i++) {
      if (curr_btn[i] != prev_btn[i]) {
        prev_btn[i] = curr_btn[i];
        if (prev_btn[i] == '0') {
          switch (i) {
          case 0:
            time_ms += 100;
            printf("K1 is released, time_ms = %dms\n", time_ms);
            break;
          case 1:
            time_ms -= 100;
            if (time_ms <= 100)
              time_ms = 100;
            printf("K2 is released, time_ms = %dms\n", time_ms);
            break;
          case 2:
            stop_buzzer(pwm_fd);
            break;
          }
        }
      }
    }
  }

  pthread_exit(NULL);
}

void set_buzzer_freq(int fd, int freq) {
  int ret = ioctl(fd, 1, freq);
  if (ret < 0) {
    perror("set the frequency of the buzzer");
    exit(EXIT_FAILURE);
  }
}

void stop_buzzer(int fd) {
  int ret = ioctl(fd, 0);
  if (ret < 0) {
    perror("stop the buzzer");
    exit(EXIT_FAILURE);
  }
}
