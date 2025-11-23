#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*!
 * @brief     sample
 * @param[in] filepath
 * @return    0:success/-1:failure
 */
static int sample_func(char *filepath) {
  int fd = 0;
  fd = creat(filepath, 0644);
  if (fd < 0) {
    printf("Error: creat() %s: %s\n", strerror(errno), filepath);
    return (-1);
  }
  printf("Info: file descriptor: %d\n", fd);
  close(fd);
  return (0);
}

int main(int argc, char *argv[]) {
  int rc = 0;
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <path>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  rc = sample_func(argv[1]);
  if (rc != 0) exit(EXIT_FAILURE);
  exit(EXIT_SUCCESS);
}
