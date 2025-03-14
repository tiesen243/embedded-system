#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  int leds_fd = open("/dev/leds", 0);
  if (leds_fd < 0) {
    perror("Open leds: ");
    exit(1);
  }

  int buttons_state[4] = {0, 0, 0, 0};
  int buttons_fd = open("/dev/buttons", 0);
  if (buttons_fd < 0) {
    perror("Open buttons: ");
    exit(1);
  }

  while (1) {
    char current_buttons[4];

    if (read(buttons_fd, current_buttons, sizeof(current_buttons)) !=
        sizeof(current_buttons)) {
      perror("read button: ");
      exit(0);
    }

    for (int i = 0; i < sizeof(buttons_state) / sizeof(buttons_state[0]); i++) {
      if (buttons_state[i] != current_buttons[i]) {
        buttons_state[i] = current_buttons[i];

        if (buttons_state[i] == '0') {
          if (i == 0)
            for (int _ = 0; _ < 3; _++) {
              for (int i = 0; i < 4; i++)
                ioctl(leds_fd, 1, i);
              usleep(500000);

              for (int i = 0; i < 4; i++)
                ioctl(leds_fd, 0, i);
              usleep(500000);
            }

          else if (i == 1)
            for (int _ = 0; _ < 3; i++) {
              for (int i = 0; i < 3; i++) {
                ioctl(leds_fd, 1, i);
                usleep(500000);
                ioctl(leds_fd, 0, i);
              }
            }

          /*for (int count = 0; count < 8; count++) {*/
          /*  ioctl(leds_fd, (count & 1) ? 1 : 0, 0);*/
          /*  ioctl(leds_fd, (count & 2) ? 1 : 0, 1);*/
          /*  ioctl(leds_fd, (count & 4) ? 1 : 0, 2);*/
          /*  ioctl(leds_fd, (count & 8) ? 1 : 0, 3);*/
          /*  usleep(500000);*/
          /*}*/

          /*for (int i = 0; i < 3; i++) {*/
          /*  ioctl(leds_fd, 1, i);*/
          /*  usleep(500000);*/
          /*}*/
        }
      }
    }
  }

  close(leds_fd);
  close(buttons_fd);

  return 0;
}
