#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// rt_sigprocmask
// Retreive and/or set the signal mask of the thread.

// int sigprocmask(int how, const sigset_t *set, sigset_t *oldset)
// how – flag to determine call behavior
// set – new signal mask (NULL to leave unchanged)
// oldset – previous signal mask
// Returns zero upon success.

// how flags
// SIG_BLOCK – set mask to block according to set
// SIG_UNBLOCK – set mask to allow according to set
// SIG_SETMASK – set mask to set

// The rt_sigprocmask system call in C is used to examine and change the signal
// mask of a process, which controls the delivery of signals. Here’s a basic
// example of how it can be used:
int main() {
  sigset_t new_mask, old_mask;
  printf("Size of sigset_t: %zu bytes \n", sizeof(sigset_t));

  // Initialize a signal set
  sigemptyset(&new_mask);
  sigaddset(&new_mask, SIGINT);  // Block SIGINT signal

  // Set the signal mask to block SIGINT
  if (sigprocmask(SIG_BLOCK, &new_mask, &old_mask) == -1) {
    perror("sigprocmask");
    exit(EXIT_FAILURE);
  }

  // Critical section: SIGINT is blocked here

  // Restore the old signal mask
  if (sigprocmask(SIG_SETMASK, &old_mask, NULL) == -1) {
    perror("sigprocmask");
    exit(EXIT_FAILURE);
  }

  return 0;
}
