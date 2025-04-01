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

#define ON 1
#define OFF 0

int main(int argc, char *argv[]) {
  int leds_fd;
  int leds[4] = {0, 1, 2, 3};
  int buttons_fd;
  char buttons[4] = {'0', '0', '0', '0'};

  leds_fd = open("/dev/leds", 0);
  if (leds_fd < 0) {
    perror("Open leds: ");
    exit(0);
  }

  buttons_fd = open("/dev/buttons", 0);
  if (buttons_fd < 0) {
    perror("Open buttons: ");
    exit(0);
  }

  while (1) {
    char current_buttons[8];

    if (read(buttons_fd, current_buttons, sizeof(current_buttons)) !=
        sizeof(current_buttons)) {
      perror("read button: ");
      exit(0);
    }

    for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
      if (buttons[i] != current_buttons[i]) {
        buttons[i] = current_buttons[i];

        if (buttons[i] == '1')
          ioctl(leds_fd, ON, leds[i]);
        else
          ioctl(leds_fd, OFF, leds[i]);
      }
    }
  }

  close(leds_fd);
  close(buttons_fd);

  return 0;
}
