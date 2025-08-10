#define _GNU_SOURCE  // Enable GNU extensions for pwrite64
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// pwrite64
// Write to file or device starting at a specific offset.

// ssize_t pwrite64(int fd, void *buf, size_t count, off_t offset)
// fd – file descriptor
// buf – pointer to buffer
// count – bytes to write
// offset – offset to start writing
// Returns bytes written.
int main(void) {
  int fd = open("out.bin", O_CREAT | O_RDWR, 0644);
  if (fd < 0) {
    perror("open");
    return 1;
  }

  const char *s = "Hello pwrite64\n";
  ssize_t n =
      pwrite64(fd, s, strlen(s), (off_t)1024);  // write at byte offset 1024
  if (n < 0) {
    perror("pwrite64");
    close(fd);
    return 1;
  }

  close(fd);
  return 0;
}
