#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>  // Required for wait()
#include <unistd.h>

// pipe
// Create a pipe.

// int pipe(int pipefd[2])
// pipefd – array of file descriptors with two ends of the pipe
// Returns zero on success.

int main() {
  int pipefd[2];  // pipefd[0] for read, pipefd[1] for write
  pid_t pid;
  char buffer[256];
  const char *message = "Hello from parent!";

  // Create the pipe
  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  // Fork a child process
  pid = fork();
  printf("1 pid: %d, buffer: %s\n", pid, buffer);

  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {      // Child process
    close(pipefd[1]);  // Close the write end in the child

    // Read from the pipe
    printf("1-2 pid: %d, buffer: %s\n", pid, buffer);
    ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer));
    printf("2 pid: %d, buffer: %s\n", pid, buffer);
    if (bytes_read == -1) {
      perror("read");
      exit(EXIT_FAILURE);
    }
    printf("3 pid: %d, buffer: %s\n", pid, buffer);
    buffer[bytes_read] = '\0';  // Null-terminate the string
    printf("Child received: %s\n", buffer);

    close(pipefd[0]);  // Close the read end in the child
  } else {             // Parent process
    close(pipefd[0]);  // Close the read end in the parent

    // Write to the pipe
    if (write(pipefd[1], message, strlen(message)) == -1) {
      perror("write");
      exit(EXIT_FAILURE);
    }
    printf("Parent sent: %s\n", message);

    close(pipefd[1]);  // Close the write end in the parent
    wait(NULL);        // Wait for the child process to terminate
  }

  return 0;
}

// int pipefd[2];:
// An integer array pipefd is declared to store the two file
// descriptors. pipefd[0] will be the read end, and pipefd[1] will be the write
// end.

// if (pipe(pipefd) == -1):
// The pipe() system call is invoked. If it returns -1,
// an error occurred.

// pid = fork();:
// A new child process is created using fork().

// Child Process (pid == 0):
//   close(pipefd[1]);:
//   The child closes its write end of the pipe because it will
// only be reading.
//   read(pipefd[0], buffer, sizeof(buffer));:
//   The child reads data from the read end of the pipe into buffer.
//   close(pipefd[0]);:
//   The child closes its read end after reading.

// Parent Process (else):
//   close(pipefd[0]);:
//   The parent closes its read end of the pipe because it will
// only be writing.
//   write(pipefd[1], message, strlen(message));:
//   The parent writes the message to the write end of the pipe.
//   close(pipefd[1]);:
//   The parent closes its write end after writing.
//   wait(NULL);:
//   The parent waits for the child process to complete before exiting.
