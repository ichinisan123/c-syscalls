#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

/// mprotect
/// Sets or adjusts protection on a region of memory.
/// int mprotect(void *addr, size_t len, int prot)
/// addr – pointer to region in memory
/// prot – protection flag
/// Returns zero when successful.
///
/// prot flags
/// PROT_NONE – prevents access to memory
/// PROT_READ – allows reading of memory
/// PROT_EXEC – allows execution of memory
/// PROT_WRITE – allows memory to be modified
/// PROT_SEM – allows memory to be used in atomic operations
/// PROT_GROWSUP – sets protection mode upward (for arcitectures that have stack
/// that grows upward)
/// PROT_GROWSDOWN – sets protection mode downward (useful for stack memory)
int main() {
  long page_size = sysconf(_SC_PAGE_SIZE);
  char *buffer = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  if (buffer == MAP_FAILED) {
    perror("mmap failed");
    return 1;
  }

  printf("Buffer allocated at: %p\n", buffer);
  printf("1: Buffer contents: %s\n", buffer);

  // Write to the buffer
  buffer[0] = 'A';
  printf("Wrote 'A' to buffer[0]\n");

  // Change protection to read-only
  if (mprotect(buffer, page_size, PROT_READ) == -1) {
    perror("mprotect failed");
    munmap(buffer, page_size);
    return 1;
  }
  printf("2: Buffer contents: %s\n", buffer);
  printf("Buffer protection changed to read-only.\n");

  // Attempt to write to the read-only buffer (will cause segmentation fault)
  buffer[0] = 'B';  // This line would cause a SIGSEGV
  printf("3: Buffer contents: %s\n", buffer);

  // Cleanup
  munmap(buffer, page_size);
  return 0;
}