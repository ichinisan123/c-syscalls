#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For STDIN_FILENO

/// @brief
// poll
// Wait for an event to occur on the specified file descriptor.
// int poll(struct pollfd *fds, nfds_t nfds, int timeout);
// fds – pointer to an array of pollfd structures (described below)
// nfds – number of pollfd items in the fds array
// timeout – sets the number of milliseconds the syscall should block (negative
// timeout > 0: poll() waits for the specified number of milliseconds.
// timeout = 0: poll() returns immediately, checking the current state of the
// file descriptors.
// timeout = -1: poll() blocks indefinitely until an event
// occurs or the call is interrupted. forces poll to return immediately)
/// @return
int main() {
  struct pollfd fds[1];   // Array to hold pollfd structures
  int timeout_ms = 5000;  // 5-second timeout

  // Initialize the pollfd structure for standard input
  fds[0].fd = STDIN_FILENO;  // File descriptor for standard input
  fds[0].events = POLLIN;    // Events to monitor: data available for reading
  fds[0].revents = 0;        // Returned events (initialized to 0)

  printf("Monitoring standard input for 5 seconds...\n");

  // Call poll()
  int ret = poll(fds, 1, timeout_ms);

  if (ret == -1) {
    perror("poll");  // Handle error
    return EXIT_FAILURE;
  } else if (ret == 0) {
    printf("Timeout occurred: No input received within 5 seconds.\n");
  } else {
    // Check if the event occurred on standard input
    if (fds[0].revents & POLLIN) {
      printf("Input available on standard input!\n");
      char buffer[256];
      ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
      if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("Read: %s", buffer);
      }
    }
  }

  return EXIT_SUCCESS;
}
// events and revents Flags:
// Common flags used in events and returned in revents include:
// POLLIN: Data available for reading.
// POLLOUT: File descriptor ready for writing.
// POLLERR: An error condition occurred.
// POLLHUP: Hang up occurred (e.g., peer closed connection).
// POLLNVAL: Invalid request.

// Return Value:
// Positive value: The number of file descriptors that have events or errors
// reported (i.e., revents is non-zero). 0: The call timed out, and no file
// descriptors were ready. -1: An error occurred, and errno is set accordingly.

// Usage:
// poll() is often used in server applications to handle multiple client
// connections concurrently. Instead of blocking on a single read() or accept()
// call, a server can use poll() to determine which client sockets are ready for
// I/O and then process them accordingly. This allows for efficient multiplexing
// of I/O operations and improved responsiveness.