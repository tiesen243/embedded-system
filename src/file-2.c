#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char buttons[8] = {'0', '0', '0', '0', '0', '0', '0', '0'};
  int buttons_fd = open("/dev/buttons", 0);
  if (buttons_fd < 0) {
    perror("Open buttons");
    return EXIT_FAILURE;
  }

  FILE *text = fopen("./input.txt", "rw");
  int count = 0;

  while (1) {
    int i;
    char current_buttons[8];

    if (read(buttons_fd, current_buttons, sizeof(current_buttons)) !=
        sizeof(current_buttons)) {
      perror("read button: ");
      exit(0);
    }

    for (i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
      if (buttons[i] != current_buttons[i]) {
        buttons[i] = current_buttons[i];

        if (buttons[i] == '0') {
          if (i == 0) {
            char c;
            do {
              c = fgetc(text);
              if (c == 'a')
                count++;
            } while (c != EOF);

            printf("Count: %d\n", count);
          } else if (i == 1) {
          } else if (i == 2) {
          }
        }
      }
    }
  }

  close(buttons_fd);
  fclose(text);
  return EXIT_SUCCESS;
}
