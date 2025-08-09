#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <string.h>

/// rt_sigaction
/// Change action taken when process receives a specific signal
/// (except SIGKILL and SIGSTOP).
/// int rt_sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)
/// signum – signal number
/// act – structure for the new action
/// oldact – structure for the old action

// Signal handler function
void handle_sigint(int signum) {
  if (signum == SIGINT) {
    printf("Caught SIGINT (Ctrl+C)!\n");
  }
}

int main() {
  struct sigaction sa;

  // Initialize sigaction structure
  sa.sa_handler = handle_sigint;  // Specify the signal handler function
  printf("sa.sa_handler = %p\n", (void *)sa.sa_handler);
  // Clear the signal mask (no signals blocked during handler execution)
  sigemptyset(&sa.sa_mask);
  printf("sa.sa_mask = %p %d\n", (void *)&sa.sa_mask, (int)sa.sa_mask.__val[0]);

  sa.sa_flags = 0;  // No special flags

  // Register the signal handler for SIGINT
  if (sigaction(SIGINT, &sa, NULL) == -1) {
    perror("Error setting up signal handler");
    return 1;
  }

  printf(
      "Press Ctrl+C to trigger the signal handler. Press Ctrl+Z to suspend.\n");

  // Keep the program running to allow signal delivery
  while (1) {
    sleep(1);  // Sleep for 1 second
  }

  return 0;
}

// #include <signal.h>:
// This header provides the sigaction structure and related functions.

// handle_sigint(int signum):
// This is the signal handler function that will be executed when SIGINT is
// received. It takes the signal number as an argument.

// struct sigaction sa;:
// A sigaction structure is declared to configure the signal handling.

// sa.sa_handler = handle_sigint;:
// The sa_handler member is set to the address of our signal handler function.

// sigemptyset(&sa.sa_mask);:
// This initializes sa_mask to an empty set, meaning
// no additional signals will be blocked while handle_sigint is executing.

// sa.sa_flags = 0;:
// No special flags are set in this example. Common flags
// include SA_RESTART (to restart interrupted system calls) and SA_SIGINFO (to
// receive extended signal information).

// sigaction(SIGINT, &sa, NULL):
// This is the core call.
// SIGINT: The signal we are handling (Ctrl+C).
// &sa: A pointer to our configured sigaction structure.
// NULL: We are not interested in retrieving the old signal action.

// while (1) { sleep(1); }:
// This loop keeps the program running indefinitely,
// allowing you to send SIGINT (by pressing Ctrl+C) and observe the signal
// handler in action.

// struct sigaction {
//     void     (*sa_handler)(int);
//     void     (*sa_sigaction)(int, siginfo_t *, void *);
//     sigset_t   sa_mask;
//     int        sa_flags;
//     void     (*sa_restorer)(void);
// };

// siginfo_t {
//     int      si_signo;      /* signal number */
//     int      si_errno;      /* errno value */
//     int      si_code;       /* signal code */
//     int      si_trapno;     /* trap that caused hardware signal (unusued on
// most architectures) */
//     pid_t    si_pid;        /* sending PID */
//     uid_t    si_uid;        /* real UID of sending program */
//     int      si_status;     /* exit value or signal */
//     clock_t  si_utime;      /* user time consumed */
//     clock_t  si_stime;      /* system time consumed */
//     sigval_t si_value;      /* signal value */
//     int      si_int;        /* POSIX.1b signal */
//     void    *si_ptr;        /* POSIX.1b signal */
//     int      si_overrun;    /* count of timer overrun */
//     int      si_timerid;    /* timer ID */
//     void    *si_addr;       /* memory location that generated fault */
//     long     si_band;       /* band event */
//     int      si_fd;         /* file descriptor */
//     short    si_addr_lsb;   /* LSB of address */
//     void    *si_lower;      /* lower bound when address vioation occured */
//     void    *si_upper;      /* upper bound when address violation occured */
//     int      si_pkey;       /* protection key on PTE causing faut */
//     void    *si_call_addr;  /* address of system call instruction */
//     int      si_syscall;    /* number of attempted syscall */
//     unsigned int si_arch;   /* arch of attempted syscall */
// }
