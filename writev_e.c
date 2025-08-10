#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/uio.h>  // Required for struct iovec and writev
#include <unistd.h>   // Required for writev

// writev
// Write to file or device from multiple buffers.

// ssize_t writev(int fd, const struct iovec *iov, int iovcnt)
// fd – file descriptor
// iov – pointer to iovec structue
// iovcnt – number of buffers (described by iovec)
// struct iovec {
//     void  *iov_base;    /* Starting address */
//     size_t iov_len;     /* Number of bytes to transfer */
// };
// Returns bytes written.

int main() {
  // Define three different strings (buffers)
  char *buf1 = "Hello, ";
  char *buf2 = "world";
  char *buf3 = "!\n";

  // Create an array of iovec structures
  // Each iovec structure describes a buffer to be written
  struct iovec iov[3];

  // Populate the iovec structures
  iov[0].iov_base = buf1;
  iov[0].iov_len = strlen(buf1);

  iov[1].iov_base = buf2;
  iov[1].iov_len = strlen(buf2);

  iov[2].iov_base = buf3;
  iov[2].iov_len = strlen(buf3);

  // Call writev to write the data to standard output (file descriptor 1)
  // The last argument is the number of iovec structures in the array
  ssize_t bytes_written = writev(STDOUT_FILENO, iov, 3);

  // Check for errors and print the number of bytes written
  if (bytes_written == -1) {
    perror("writev");
    return EXIT_FAILURE;
  } else {
    printf("Successfully wrote %zd bytes.\n", bytes_written);
  }

  return EXIT_SUCCESS;
}