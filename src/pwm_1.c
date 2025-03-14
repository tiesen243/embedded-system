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
  int fd, freq = 500;

  fd = open("/dev/pwm", 0);
  if (fd < 0) {
    perror("open pwm_buzzer device");
    exit(1);
  }

  printf("\nBUZZER TEST (PWM Control)\n");
  set_buzzer_freq(fd, freq);
  printf("> Freq = %d\n", freq);

  while (1) {
    freq += 100;
    if (freq > 2000) {
      printf("> Stop PWM");
      stop_buzzer(fd);
    } else {
      printf("> Freq = %d\n", freq);
      set_buzzer_freq(fd, freq);
      sleep(2);
    }
  }
}
