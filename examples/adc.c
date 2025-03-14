#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("Press Ctrl+C to stop\n");
  int fd = open("/dev/adc", 0);
  if (fd < 0) {
    perror("Open ADC device: ");
    return EXIT_FAILURE;
  }

  while (1) {
    char buffer[30];
    int len = read(fd, buffer, sizeof(buffer) - 1);
    if (len > 0) {
      buffer[len] = '\0';
      int value = -1;
    }
  }
  return EXIT_SUCCESS;
}
