#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
  int fd = 0;
  char *path = "example.txt";

  fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if (fd < 0) {
    printf("Error: open(%d) %s\n", errno, strerror(errno));
    return (-1);
  }
  printf("File descriptor: %d\n", fd);

  if (close(fd) < 0) {
    printf("Error: close(%d) %s\n", errno, strerror(errno));
    return (-1);
  }

  return (0);
}
