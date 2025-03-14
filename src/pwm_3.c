#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
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
}

int main(int argc, char *argv[]) {
  int freq = 0;
  int pwm_fd = open("/dev/pwm", 0);
  if (pwm_fd < 0) {
    perror("Open pwm: ");
    exit(0);
  }

  int buttons_state[3] = {0, 0, 0};
  int buttons_fd = open("/dev/buttons", 0);
  if (buttons_fd < 0) {
    perror("Open buttons: ");
    exit(0);
  }

  while (1) {
    char current_buttons[3];

    if (read(buttons_fd, current_buttons, sizeof(current_buttons)) !=
        sizeof(current_buttons)) {
      perror("read button: ");
      exit(0);
    }

    for (int i = 0; i < sizeof(buttons_state) / sizeof(buttons_state[0]); i++)
      if (buttons_state[i] != current_buttons[i]) {
        buttons_state[i] = current_buttons[i];

        if (buttons_state[i] != '0') {
          if (i == 0) {
            freq = 500;
            printf("> Freq: %d\n", freq);
            set_buzzer_freq(pwm_fd, freq);
          } else if (i == 1) {
            freq = 1000;
            printf("> Freq: %d\n", freq);
            set_buzzer_freq(pwm_fd, freq);
          } else if (i == 2) {
            freq = 1500;
            printf("> Freq: %d\n", freq);
            set_buzzer_freq(pwm_fd, freq);
          }
        } else {
          stop_buzzer(pwm_fd);
        }
      }
  }

  close(buttons_fd);
  close(pwm_fd);

  return 0;
}
