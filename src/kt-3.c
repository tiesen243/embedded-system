#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

static FILE *f;
static int freq = 1000, is_run_led = 0;
static char n = '0';

int pwm_fd, buttons_fd, leds_fd;
void set_buzzer_freq(int fd, int freq);
void stop_buzzer(int fd);

void *btn_polling(void *param);
void *input_polling(void *param);
void *led_polling(void *param);

int main(int argc, char *argv[]) {
  buttons_fd = open("/dev/buttons", 0);
  if (buttons_fd < 0) {
    perror("Open buttons");
    exit(EXIT_FAILURE);
  }

  pwm_fd = open("/dev/pwm", 0);
  if (pwm_fd < 0) {
    perror("Open pwm");
    exit(EXIT_FAILURE);
  }

  leds_fd = open("/dev/leds", 0);
  if (leds_fd < 0) {
    perror("Open leds");
    exit(EXIT_FAILURE);
  }

  f = fopen("./test.txt", "rw+");

  stop_buzzer(pwm_fd);

  fwrite("0123456789", 1, 10, f);

  int i;
  for (i = 0; i < 4; i++) {
    ioctl(leds_fd, 0, i);
  }

  pthread_t t1 =
      pthread_create(&t1, NULL, btn_polling, (void *)"Button thread");
  pthread_t t2 =
      pthread_create(&t2, NULL, input_polling, (void *)"Input thread");
  pthread_t t3 = pthread_create(&t3, NULL, led_polling, (void *)"Led thread");

  while (1) {
  }

  close(buttons_fd);
  close(pwm_fd);
  close(leds_fd);
  fclose(f);
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

    if (curr_btn[0] != prev_btn[0]) {
      prev_btn[0] = curr_btn[0];
      if (prev_btn[0] == '0') {
        fseek(f, 0, SEEK_SET);
        printf("\nK1 is released, content: ");
        int c;
        do {
          c = fgetc(f);
          if (c != EOF)
            printf("%c", c);
        } while (c != EOF);
        printf("\n");
      }
    }

    int j;
    if (curr_btn[2] != prev_btn[2]) {
      prev_btn[2] = curr_btn[2];
      if (prev_btn[2] == '0') {
        printf("\nK3 is released, %d\n", n - '0');

        for (j = 0; j < 4; j++)
          ioctl(leds_fd, 0, j);
        is_run_led = 1;

        for (j = 0; j < n - '0'; j++) {
          set_buzzer_freq(pwm_fd, freq);
          usleep(500000);
          stop_buzzer(pwm_fd);
          usleep(500000);
        }
        stop_buzzer(pwm_fd);

        is_run_led = 0;

        usleep(500000);
        for (j = 0; j < 4; j++)
          ioctl(leds_fd, 0, j);
      }
    }
  }

  pthread_exit(NULL);
}

void *input_polling(void *param) {
  while (1) {
    printf("\nn = ");
    scanf("%c", &n);

    int x;
    printf("\nx = ");
    scanf("%d", &x);

    if (x <= 0)
      continue;

    int i;

    fwrite(" ", 1, 1, f);

    fseek(f, 0, SEEK_SET);
    for (i = 0; i < x; i++) {
      fputc('x', f);
    }

    if (n == ' ' || n < '1' || n > '5') {
      printf("\nn khong hop le\n");
      n = '0';
      continue;
    }
  }

  pthread_exit(NULL);
}

void *led_polling(void *param) {
  while (1) {

    if (!is_run_led)
      continue;

    int i;
    if (n == '1') {
      ioctl(leds_fd, 1, 0);
    } else if (n == '2') {
      ioctl(leds_fd, 1, 0);
      ioctl(leds_fd, 1, 1);
    } else if (n == '3') {
      ioctl(leds_fd, 1, 0);
      ioctl(leds_fd, 1, 1);
      ioctl(leds_fd, 1, 2);
    } else if (n == '4') {
      for (i = 0; i < 4; i++)
        ioctl(leds_fd, 1, i);
    } else if (n == '5') {
      for (i = 0; i < 4; i++)
        ioctl(leds_fd, 1, i);
      usleep(500000);
      for (i = 0; i < 4; i++)
        ioctl(leds_fd, 0, i);
      usleep(500000);
    }
  }
}

void set_buzzer_freq(int fd, int freq) {
  int ret = ioctl(fd, 1, freq);
  if (ret < 0) {
    perror("set the frequency of the buzzer");
    exit(EXIT_FAILURE);
  }
}

void stop_buzzer(int fd) {
  int ret = ioctl(fd, 0);
  if (ret < 0) {
    perror("stop the buzzer");
    exit(EXIT_FAILURE);
  }
}
