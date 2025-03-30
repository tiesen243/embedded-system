#include <stdio.h>

int main(int argc, char *argv[]) {
  FILE *fp = fopen("./log", "wb");

  fputs("This is an apple.", fp);
  fseek(fp, 9, SEEK_SET);
  fputs(" sam", fp);

  fclose(fp);
  return 0;
}
