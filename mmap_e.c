#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

/// @brief
/// mmap
/// Maps files or devices into memory.
/// void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
/// addr – location hint for mapping location in memory, otherwise, if NULL,
/// kernel assigns address
/// length – length of the mapping
/// prot – specifies memory protection of the mapping
/// flags – control visibility of mapping with other processes
/// fd – file descriptor
/// offset – file offset
/// Returns a pointer to the mapped file in memory.
///
/// prot flags
/// PROT_EXEC – allows execution of mapped pages
/// PROT_READ – allows reading of mapped pages
/// PROT_WRITE – allows mapped pages to be written
/// PROT_NONE – prevents access of mapped pages
///
/// flags
/// MAP_SHARED – allows other processes to use this mapping
/// MAP_SHARED_VALIDATE – same as MAP_SHARED but ensures all flags are valid
/// MAP_PRIVATE – prevents other processes from using this mapping
/// MAP_32BIT – tells the kernel to locate mapping in the first 2 GB of RAM
/// MAP_ANONYMOUS – lets the mapping not be backed by any file (thus ignoring
/// fd)
/// MAP_FIXED – treats addr argument as an actual address and not a hint
/// MAP_FIXED_NOREPLACE – same as MAP_FIXED but prevents clobbering existing
/// mapped ranges
/// MAP_GROWSDOWN – tells the kernel to expand mapping downward in
/// RAM (useful for stacks)
/// MAP_HUGETB – forces use of huge pages in mapping
/// MAP_HUGE_1MB – use with MAP_HUGETB to set 1 MB pages
/// MAP_HUGE_2MB – use with MAP_HUGETB to set 2 MB pages
/// MAP_LOCKED – maps the region to be locked (similar behavior to mlock)
/// MAP_NONBLOCK – prevents read-ahead for this mapping
/// MAP_NORESERVE – prevents allocation of swap space for this mappining
/// MAP_POPULATE – tells the kernel to populate page tables for this mapping
/// (causing read-ahead)
/// MAP_STACK – tells the kernel to allocate address
/// suitable for use in a stack
/// MAP_UNINITIALIZED – prevents clearing of anonymous pages
/// @return
int main() {
  int fd = open("example.txt", O_RDWR | O_CREAT, 0644);
  if (fd == -1) {
    perror("open");
    return 1;
  }

  // Write some initial data to the file
  const char *initial_data = "Hello mmap!";
  write(fd, initial_data, strlen(initial_data));

  // Map the file into memory
  char *mapped_memory = mmap(NULL, strlen(initial_data), PROT_READ | PROT_WRITE,
                             MAP_SHARED, fd, 0);
  if (mapped_memory == MAP_FAILED) {
    perror("mmap");
    close(fd);
    return 1;
  }

  // Access and modify the file content through the mapped memory
  printf("Original content: %s\n", mapped_memory);
  mapped_memory[0] = 'H';
  mapped_memory[1] = 'i';
  printf("Modified content: %s\n", mapped_memory);

  // Unmap the memory and close the file descriptor
  if (munmap(mapped_memory, strlen(initial_data)) == -1) {
    perror("munmap");
  }
  close(fd);

  return 0;
}