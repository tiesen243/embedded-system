#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char buttons[6] = {'0', '0', '0', '0', '0', '0'};
  int buttons_fd = open("/dev/buttons", 0);
  if (buttons_fd < 0) {
    perror("Open buttons");
    exit(EXIT_FAILURE);
  }

  FILE *f = fopen("./input.txt", "rw");

  while (1) {
    int i;
    char current_buttons[6];

    if (read(buttons_fd, current_buttons, sizeof(current_buttons)) !=
        sizeof(current_buttons)) {
      perror("read button: ");
      exit(EXIT_FAILURE);
    }

    for (i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
      if (buttons[i] != current_buttons[i]) {
        buttons[i] = current_buttons[i];

        if (buttons[i] == '0') {
          if (i == 0) {
            int c, count = 0;

            do {
              c = fgetc(f);
              printf("get: %c\n", c);
              if (c == 'a')
                count++;
            } while (c != EOF);

            printf("Number of 'a' characters: %d\n", count);
          } else if (i == 1) {
            fseek(f, 0, SEEK_SET);
            int c;
            while ((c = fgetc(f)) != EOF) {
              if (c == 'a') {
                fseek(f, -1, SEEK_CUR);
                fputc('A', f);
                break;
              }
            }
          } else if (i == 2) {
            fseek(f, 0, SEEK_END);
            fputc('a', f);
          }
        }
      }
    }
  }

  fclose(f);
  close(buttons_fd);
  return EXIT_SUCCESS;
}
