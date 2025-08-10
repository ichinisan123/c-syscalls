#include <fcntl.h>  // Required for open()
#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>  // Required for struct iovec and readv()
#include <unistd.h>   // Required for close()

// readv
// Read from file or device into multiple buffers.

// ssize_t readv(int fd, const struct iovec *iov, int iovcnt)
// fd – file descriptor
// iov – pointer to iovec structue
// iovcnt – number of buffers (described by iovec)
// struct iovec {
//     void  *iov_base;    /* Starting address */
//     size_t iov_len;     /* Number of bytes to transfer */
// };
// Returns bytes read.

int main() {
  int fd;
  char buffer1[20];
  char buffer2[10];
  char buffer3[15];
  struct iovec iov[3];
  ssize_t bytes_read;

  // Open a file for reading
  fd = open("example.txt", O_RDWR | O_CREAT, 0644);
  if (fd == -1) {
    perror("Error opening file");
    return 1;
  }
  printf("fd: %d\n", fd);
  // Write some data to the file for demonstration
  write(fd,
        "This is some data for buffer 1. And more for buffer 2.Finally, for "
        "buffer 3.",
        75);
  lseek(fd, 0, SEEK_SET);  // Rewind to the beginning of the file

  // Set up the iovec structures
  iov[0].iov_base = buffer1;
  iov[0].iov_len = sizeof(buffer1) - 1;

  iov[1].iov_base = buffer2;
  iov[1].iov_len = sizeof(buffer2) - 1;

  iov[2].iov_base = buffer3;
  iov[2].iov_len = sizeof(buffer3) - 1;

  // Read data into the buffers using readv()
  bytes_read = readv(fd, iov, 3);

  if (bytes_read == -1) {
    perror("Error reading with readv()");
    close(fd);
    return 1;
  }

  printf("Bytes read: %zd\n", bytes_read);

  // Null-terminate the buffers for safe printing
  buffer1[sizeof(buffer1) - 1] = '\0';
  buffer2[sizeof(buffer2) - 1] = '\0';
  buffer3[sizeof(buffer3) - 1] = '\0';

  printf("Buffer 1: %s\n", buffer1);
  printf("Buffer 2: %s\n", buffer2);
  printf("Buffer 3: %s\n", buffer3);

  close(fd);
  return 0;
}