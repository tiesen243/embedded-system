#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

int leds_fd, buttons_fd;
static int time_ms = 1000;

void *btn_polling(void *param);

int main(int argc, char *argv[]) {
  leds_fd = open("/dev/leds", 0);
  if (leds_fd < 0) {
    perror("open pwm");
    exit(EXIT_FAILURE);
  }

  buttons_fd = open("/dev/buttons", 0);
  if (buttons_fd < 0) {
    perror("open buttons");
    exit(EXIT_FAILURE);
  }

  pthread_t t = pthread_create(&t, NULL, btn_polling, (void *)"Button thread");

  while (1) {
    int i;
    for (i = 0; i < 4; i++) {
      ioctl(leds_fd, 1, i);
      usleep(time_ms * 1000);
      ioctl(leds_fd, 0, i);
    }
  }

  close(leds_fd);
  close(buttons_fd);

  return EXIT_SUCCESS;
}

void *btn_polling(void *param) {
  char curr_btn[3], prev_btn[3] = {'0', '0', '0'};

  while (1) {
    int num = read(buttons_fd, curr_btn, sizeof(curr_btn));
    if (num != sizeof(curr_btn)) {
      perror("read buttons");
      exit(EXIT_FAILURE);
    }

    int i;
    for (i = 0; i < 3; i++) {
      if (curr_btn[i] != prev_btn[i]) {
        prev_btn[i] = curr_btn[i];
        if (prev_btn[i] == '0') {
          switch (i) {
          case 0:
            time_ms += 100;
            printf("K1 is released, time_ms = %dms\n", time_ms);
            break;
          case 1:
            time_ms -= 100;
            if (time_ms <= 100)
              time_ms = 100;
            printf("K2 is released, time_ms = %dms\n", time_ms);
            break;
          case 2:
            time_ms = 1000;
            printf("K3 is released, time_ms = %dms\n", time_ms);
            break;
          }
        }
      }
    }
  }

  pthread_exit(NULL);
}
