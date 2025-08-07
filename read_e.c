#include <fcntl.h>  // For open()
#include <stdio.h>
#include <unistd.h>  // For read()

/// @brief
/// read
/// Reads from a specified file using a file descriptor. Before using this call,
/// you must first obtain a file descriptor using the opensyscall. Returns bytes
/// read successfully. ssize_t read(int fd, void *buf, size_t count)
/// @param fd – file descriptor
/// @param buf - pointer to the buffer to fill with read contents
/// @param count – number of bytes to read
/// @return number of bytes read on success, -1 on error
int main() {
  int fd;
  char buffer[1024];  // Buffer to store read data
  ssize_t bytes_read;

  // Open a file for reading
  fd = open("example.txt", O_RDONLY);
  if (fd == -1) {
    perror("Error opening file");
    return 1;
  }
  printf("File opened successfully with file descriptor: %d\n", fd);
  // Read data from the file into the buffer
  bytes_read =
      read(fd, buffer, sizeof(buffer) - 1);  // Leave space for null terminator
  if (bytes_read == -1) {
    perror("Error reading from file");
    close(fd);
    return 1;
  }

  // Null-terminate the buffer if reading text
  buffer[bytes_read] = '\0';

  // Print the read content
  printf("Content read from file:\n%s\n", buffer);

  // Close the file descriptor
  close(fd);

  return 0;
}