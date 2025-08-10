#define _GNU_SOURCE  // Enable GNU extensions for pread64
#include <errno.h>   // For errno and perror
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// pread64
// Read from file or device starting at a specific offset.

// ssize_t pread64(int fd, void *buf, size_t count, off_t offset)
// fd – file descriptor
// buf – pointer to read buffer
// count – bytes to read
// offset – offset to read from
// Returns bytes read.

int main() {
  int fd;
  char buffer[100];
  ssize_t bytes_read;
  off64_t offset = 0;  // Starting offset for the read
  // off_t offset = 0;  // Starting offset for the read

  // Create a dummy file for demonstration
  fd = open("test_file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
  if (fd == -1) {
    perror("Error creating file");
    return 1;
  }
  const char *data = "This is some sample data for pread64 demonstration.";
  if (write(fd, data, strlen(data)) == -1) {
    perror("Error writing to file");
    close(fd);
    return 1;
  }
  close(fd);  // Close the file after writing

  // Open the file for reading
  fd = open("test_file.txt", O_RDONLY);
  if (fd == -1) {
    perror("Error opening file for reading");
    return 1;
  }

  // Read 10 bytes from offset 5
  offset = 5;
  // bytes_read = pread(fd, buffer, 10, offset);
  bytes_read = pread64(fd, buffer, 10, offset);

  if (bytes_read == -1) {
    perror("Error reading with pread64");
    close(fd);
    return 1;
  } else if (bytes_read == 0) {
    printf("End of file reached or no bytes read.\n");
  } else {
    buffer[bytes_read] = '\0';  // Null-terminate the read data
    printf("Read %zd bytes from offset %lld: \"%s\"\n", bytes_read,
           (long long)offset, buffer);
  }

  // Read another 5 bytes from offset 20
  offset = 20;
  bytes_read = pread64(fd, buffer, 5, offset);
  // bytes_read = pread(fd, buffer, 5, offset);
  if (bytes_read == -1) {
    perror("Error reading with pread64");
    close(fd);
    return 1;
  } else if (bytes_read == 0) {
    printf("End of file reached or no bytes read.\n");
  } else {
    buffer[bytes_read] = '\0';  // Null-terminate the read data
    printf("Read %zd bytes from offset %lld: \"%s\"\n", bytes_read,
           (long long)offset, buffer);
  }

  close(fd);  // Close the file descriptor

  // Clean up the dummy file
  if (unlink("test_file.txt") == -1) {
    perror("Error deleting file");
  }

  return 0;
}