#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>  // For exit()
#include <unistd.h>  // For open(), close(), and perror()

/// @brief
/// open
/// Opens or creates a file, depending on the flags passed to the call. Returns
/// an integer with the file descriptor.
/// int open(const char *pathname, int flags, mode_t mode)
/// pathname - pointer to a buffer containing the full path and filename
/// flags - integer with operation flags (see below)
/// mode - (optional) defines the permissions mode if file is to be created
/// 0644 is a common mode, which means read/write for owner 6, and read for
/// group and others 4 4. Returns a file descriptor (an integer) on success, or
/// -1 on error. close Close a file descriptor. After successful execution, it
/// can no longer be used to reference the file. int close(int fd) fd - file
/// descriptor to close
/// @return
int main() {
  int fd;
  // Open an existing file for reading
  fd = open("example.txt", O_RDONLY);
  if (fd == -1) {
    perror("Error opening file for reading");
    exit(EXIT_FAILURE);
  }
  printf("File opened for reading with descriptor: %d\n", fd);
  // Close the file when done
  if (close(fd) == -1) {
    perror("Error closing file");
    exit(EXIT_FAILURE);
  }

  // Create a new file for writing, with specific permissions
  fd = open("example2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd == -1) {
    perror("Error creating file for writing");
    exit(EXIT_FAILURE);
  }
  printf("New file created for writing with descriptor: %d\n", fd);
  // Close the file when done
  if (close(fd) == -1) {
    perror("Error closing file");
    exit(EXIT_FAILURE);
  }

  return 0;
}
/*
open flags

O_APPEND - append to existing file
O_ASYNC - use signal-driven IO
O_CLOEXEC - use close-on-exec (avoid race conditions and lock contentions)
O_CREAT - create file if it doesn't exist
O_DIRECT - bypass cache (slower)
O_DIRECTORY - fail if pathname isn't a directory
O_DSYNC - ensure output is sent to hardware and metadata written before return
O_EXCL - ensure creation of file
O_LARGEFILE - allows use of file sizes represented by off64_t
O_NOATIME - do not increment access time upon open
O_NOCTTY - if pathname is a terminal device, don't become controlling terminal
O_NOFOLLOW - fail if pathname is symbolic link
O_NONBLOCK - if possible, open file with non-blocking IO
O_NDELAY - same as O_NONBLOCK
O_PATH - open descriptor for obtaining permissions and status of a file but does
not allow read/write operations
O_SYNC - wait for IO to complete before returning
O_TMPFILE - create an unnamed, unreachable (via any other open call) temporary
file
O_TRUNC - if file exists, ovewrite it (careful!)
*/