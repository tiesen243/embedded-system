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
#define ESC_KEY 0x1b

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
  printf("Press 'ESC+ENTER' key to Exit this program\n\n");
  set_buzzer_freq(fd, freq);
  printf("\tFreq = %d\n", freq);

  while (1) {
    freq += 100;
    if (freq == 2000) {
      printf("Stop PWD");
      stop_buzzer(fd);
    } else {
      set_buzzer_freq(fd, freq);
      sleep(2);
    }
  }
}
