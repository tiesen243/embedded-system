#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char buttons[6] = {'0', '0', '0', '0', '0', '0'};
  int buttons_fd = open("/dev/buttons", 0);
  if (buttons_fd < 0) {
    perror("Open buttons");
    return EXIT_FAILURE;
  }

  FILE *text = fopen("./text.txt", "rw");
  int count = 0;

  while (1) {
    int i;
    char current_buttons[6];

    if (read(buttons_fd, current_buttons, sizeof(current_buttons)) !=
        sizeof(current_buttons)) {
      perror("read button");
      exit(EXIT_FAILURE);
    }

    for (i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
      if (buttons[i] != current_buttons[i]) {
        buttons[i] = current_buttons[i];

        if (buttons[i] == '0') {
          if (i == 0) {
            count++;
            fseek(text, 0, SEEK_SET);
            fputs((const char *)&count, text);
          } else if (i == 1) {
            fread(&count, sizeof(int), 1, text);
            printf("Count: %d\n", count);
          } else if (i == 2) {
            count = 0;
            fseek(text, 0, SEEK_SET);
            fputs((const char *)&count, text);
          }
        }
      }
    }
  }

  close(buttons_fd);
  fclose(text);
  return EXIT_SUCCESS;
}
