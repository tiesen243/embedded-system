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
  int leds_fd = open("/dev/leds", 0);
  if (leds_fd < 0) {
    perror("Open leds: ");
    exit(0);
  }

  for (int i = 0; i < 4; i++)
    ioctl(leds_fd, 1, i);

  while (1) {
    char val = getchar();
    printf("val: %c\n", val);

    if (val == '1') {
      for (int i = 0; i <= 3; i++) {
        ioctl(leds_fd, 0, i);
        usleep(500000);
      }

      for (int i = 3; i >= 0; i--) {
        ioctl(leds_fd, 1, i);
        usleep(500000);
      }

      val = '9';
    }

    if (val == '2') {
      for (int _ = 0; _ < 2; _++) {
        for (int i = 0; i <= 3; i++) {
          ioctl(leds_fd, 0, i);
          usleep(500000);
        }

        for (int i = 3; i >= 0; i--) {
          ioctl(leds_fd, 1, i);
          usleep(500000);
        }
      }

      val = '9';
    }

    if (val == '3') {
      for (int i = 0; i <= 3; i++) {
        ioctl(leds_fd, 0, i);
      }

      val = '9';
    }
  }

  close(leds_fd);

  return 0;
}
