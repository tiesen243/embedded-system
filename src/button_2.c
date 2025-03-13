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

int main(int argc, char *argv[]) {
  int leds_state[4] = {0, 0, 0, 0};
  int leds_fd = open("/dev/leds", 0);
  if (leds_fd < 0) {
    perror("Open leds: ");
    exit(0);
  }

  int buttons_state[4] = {0, 0, 0, 0};
  int buttons_fd = open("/dev/buttons", 0);
  if (buttons_fd < 0) {
    perror("Open buttons: ");
    exit(0);
  }

  for (int i = 0; i < sizeof(leds_state) / sizeof(leds_state[0]); i++)
    ioctl(leds_fd, leds_state[i], i);

  while (1) {
    char current_buttons[4];

    if (read(buttons_fd, current_buttons, sizeof(current_buttons)) !=
        sizeof(current_buttons)) {
      perror("read button: ");
      exit(0);
    }

    for (int i = 0; i < sizeof(buttons_state) / sizeof(buttons_state[0]); i++)
      if (current_buttons[i] == 0 && buttons_state[i] == 1) {
        leds_state[i] = ~leds_state[i];
        ioctl(leds_fd, leds_state[i], i);
      }
  }

  close(leds_fd);
  close(buttons_fd);

  return 0;
}
