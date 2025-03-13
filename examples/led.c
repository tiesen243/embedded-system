
#include <fcntl.h>
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
  leds_fd = open("/dev/leds", 0);
  if (leds_fd < 0) {
    perror("Open led: ");
    exit(0);
  }

  while (1) {
    int i;
    ioctl(leds_fd, ON, 0);

    sleep(1);

    ioctl(leds_fd, OFF, 0);

    sleep(1);
  }

  close(leds_fd);
  return 0;
}
