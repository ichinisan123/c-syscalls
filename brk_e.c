#define _GNU_SOURCE  // Required for brk() on some systems
#include <errno.h>   // For errno
#include <stdio.h>   // For printf()
#include <string.h>  // For strerror()
#include <unistd.h>  // For brk() and sbrk()

/// brk
/// Allows for altering the program break that defines end of process’s data
/// segment.
/// int brk(void *addr)
/// addr – new program break address pointer
/// Returns zero when successful.
int main() {
  void *initial_break;
  void *current_break;
  void *new_break;
  char *allocated_memory;
  int size_to_allocate = 1024;  // Allocate 1KB

  // Get the initial program break
  initial_break = sbrk(0);
  if (initial_break == (void *)-1) {
    perror("sbrk(0) failed");
    return 1;
  }
  printf("Initial program break: %p\n", initial_break);

  // Increase the program break to allocate memory
  new_break = (char *)initial_break + size_to_allocate;
  if (brk(new_break) == -1) {
    perror("brk() failed to allocate memory");
    return 1;
  }
  current_break = sbrk(0);  // Get the new program break
  printf("Program break after allocation: %p\n", current_break);

  // Use the allocated memory (it's uninitialized, but can be written to)
  allocated_memory = (char *)initial_break;
  snprintf(allocated_memory, size_to_allocate,
           "Hello from brk() allocated memory!");
  printf("Content of allocated memory: %s\n", allocated_memory);

  // Decrease the program break to deallocate memory
  if (brk(initial_break) == -1) {
    perror("brk() failed to deallocate memory");
    return 1;
  }
  current_break = sbrk(0);  // Get the final program break
  printf("Program break after deallocation: %p\n", current_break);

  return 0;
}

// #define _GNU_SOURCE:
// This macro is often required on Linux systems to expose brk() and sbrk().

// sbrk(0):
// This call to sbrk() with an argument of 0 returns the current program break
// without modifying it. This is useful for getting a reference point.

// brk(new_break):
// This is the core of the brk() system call. It attempts to set the program
// break to the address specified by new_break. If successful, memory up to this
// new break becomes accessible to the process.

// Memory Usage:
// After increasing the break, the memory region between the initial_break and
// the new_break can be used. In the example, a string is written into this
// region.

// Deallocation:
// To deallocate the memory, brk() is called again, setting the program break
// back to its initial_break value. This effectively releases the allocated
// space back to the system.

// Important Considerations:
// brk() and sbrk() are low-level and less flexible than malloc() and free().
// They only allow increasing or decreasing the program break linearly.

// brk() and sbrk() operate on the program's data segment (heap).
// Error handling is crucial, as brk() can fail (e.g., due to insufficient
// memory), returning -1 and setting errno.
