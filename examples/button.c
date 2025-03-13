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
  int buttons_fd;
  char buttons[8] = {'0', '0', '0', '0', '0', '0', '0', '0'};

  buttons_fd = open("/dev/buttons", 0);
  if (buttons_fd < 0) {
    perror("Fail to open buttons");
    exit(0);
  }

  while (1) {
    char current_buttons[8];
    int count_of_changed_key, i;

    if (read(buttons_fd, current_buttons, sizeof(current_buttons)) !=
        sizeof(current_buttons)) {
      perror("read button: ");
      exit(0);
    }

    for (i = 0, count_of_changed_key = 0;
         i < sizeof(buttons) / sizeof(buttons[0]); i++) {
      if (buttons[i] != current_buttons[i]) {
        buttons[i] = current_buttons[i];
        printf("%s key %d is %s", count_of_changed_key ? ", " : "", i + 1,
               buttons[i] == '0' ? "up" : "down");
        count_of_changed_key++;
      }

      if (count_of_changed_key)
        printf("\n");
    }
  }

  close(buttons_fd);
  return 0;
}
