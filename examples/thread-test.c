#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("POSIX version is set to %ld\n", _POSIX_VERSION);
  if (_POSIX_VERSION < 199506L)
    printf("This system does not support thread\n");
  else
    printf("This system support thread\n");

  return EXIT_SUCCESS;
}
