#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#define PWM_IOCTL_SET_FREQ 1
#define PWM_IOCTL_STOP 0

void set_buzzer_freq(int fd, int freq) {
  int ret = ioctl(fd, PWM_IOCTL_SET_FREQ, freq);
  if (ret < 0) {
    perror("set the frequency of the buzzer");
    exit(1);
  }
}

void stop_buzzer(int fd) {
  int ret = ioctl(fd, PWM_IOCTL_STOP);
  if (ret < 0) {
    perror("stop the buzzer");
    exit(1);
  }
  close(fd);
}

int main(int argc, char *argv[]) {
  int freq = 1000;
  int pwm_fd = open("/dev/pwm", 0);
  if (pwm_fd < 0) {
    perror("open pwm_buzzer device");
    exit(1);
  }

  int leds_state[4] = {0, 0, 0, 0};
  int leds_fd = open("/dev/leds", 0);
  if (leds_fd < 0) {
    perror("open leds device");
    exit(1);
  }

  printf("\nBUZZER TEST (PWM Control)\n");
  set_buzzer_freq(pwm_fd, freq);
  printf("> Freq = %d\n", freq);

  while (1) {
    for (int count = 0; count < 16; count++) {
      ioctl(leds_fd, (count & 1) ? 1 : 0, 0);
      ioctl(leds_fd, (count & 2) ? 1 : 0, 1);
      ioctl(leds_fd, (count & 4) ? 1 : 0, 2);
      ioctl(leds_fd, (count & 8) ? 1 : 0, 3);
      usleep(300000);
    }

    freq += 200;
    if (freq > 2000) {
      stop_buzzer(pwm_fd);
      break;
    }
    printf("> Freq = %d\n", freq);
    set_buzzer_freq(pwm_fd, freq);
  }
}
