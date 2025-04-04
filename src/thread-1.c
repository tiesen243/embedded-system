#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

int pwm_fd, buttons_fd;
static int freq = 1000, is_running = 1;

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
    usleep(500 * 1000);
    if (is_running)
      set_buzzer_freq(pwm_fd, freq);
    else
      stop_buzzer(pwm_fd);
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

    int i;
    for (i = 0; i < 3; i++) {
      if (curr_btn[i] != prev_btn[i]) {
        prev_btn[i] = curr_btn[i];
        if (prev_btn[i] == '0') {
          switch (i) {
          case 0:
            freq += 50;
            if (freq >= 3000)
              freq = 3000;
            printf("K1 is released, freq = %dHz\n", freq);
            break;
          case 1:
            freq -= 50;
            if (freq <= 50)
              freq = 50;
            printf("K2 is released, freq = %dHz\n", freq);
            break;
          case 2:
            is_running = !is_running;
            printf("K3 is released, toggle buzzer %s\n",
                   is_running ? "ON" : "OFF");
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
