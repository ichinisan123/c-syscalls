#include <fcntl.h>   // For open() flags
#include <stdio.h>   // For printf()
#include <unistd.h>  // For lseek()

/// @brief
// lseek
// This syscall repositions the read/write offset of the associated file
// descriptor. Useful for setting the position to a specific location to read or
// write starting from that offset.
// off_t lseek(int fd, off_t offset, int whence)
// fd – file descriptor
// offset – offset to read/write from
// whence – specifies offset relation and seek behavior
// whence flags
// SEEK_SET – offset is the absolute offset position in the file
// SEEK_CUR – offset is the current offset location plus offset
// SEEK_END – offset is the file size plus offset
// SEEK_DATA – set offset to next location greater or equal to offset that
// contains data
// SEEK_HOLE – set offset to next hole in file great or equal to
// offset
// Returns resulting offset in bytes from the start of the file.
/// @return
int main() {
  int fd;
  off_t new_pos;

  // Open a file for reading and writing
  fd = open("example.txt", O_RDWR | O_CREAT, 0644);
  if (fd == -1) {
    perror("Error opening file");
    return 1;
  }

  // Write some data to the file
  write(fd, "Hello World", 11);

  // Reposition the file pointer to the beginning
  new_pos = lseek(fd, 0, SEEK_SET);
  printf("File pointer moved to position: %ld\n", (long)new_pos);

  // Reposition the file pointer 5 bytes from the current position
  new_pos = lseek(fd, 5, SEEK_CUR);
  printf("File pointer moved to position: %ld\n", (long)new_pos);

  // Reposition the file pointer 2 bytes before the end of the file
  new_pos = lseek(fd, -2, SEEK_END);
  printf("File pointer moved to position: %ld\n", (long)new_pos);

  close(fd);
  return 0;
}