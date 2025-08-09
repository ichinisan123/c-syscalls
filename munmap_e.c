#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

/// munmap
/// Unmaps mapped files or devices.
/// int munmap(void *addr, size_t len)
/// addr – pointer to mapped address
/// len – size of mapping
/// Returns zero when successful.
int main() {
  const char *filepath = "example.txt";
  const char *data_to_write = "Hello, mmap and munmap!";
  size_t file_size = strlen(data_to_write);

  // 1. Create a file for mapping
  int fd = open(filepath, O_CREAT | O_RDWR, 0666);
  if (fd == -1) {
    perror("open");
    return 1;
  }

  // 2. Set the file size
  if (ftruncate(fd, file_size) == -1) {
    perror("ftruncate");
    close(fd);
    return 1;
  }

  // 3. Map the file into memory
  void *addr = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (addr == MAP_FAILED) {
    perror("mmap");
    close(fd);
    return 1;
  }

  // Close the file descriptor after mapping (optional, but good practice)
  close(fd);

  // 4. Write data to the mapped memory
  strcpy((char *)addr, data_to_write);
  printf("Data written to mapped memory: %s\n", (char *)addr);

  // 5. Unmap the memory region
  if (munmap(addr, file_size) == -1) {
    perror("munmap");
    return 1;
  }
  printf("Memory successfully unmapped.\n");

  // Attempting to access the unmapped memory will likely result in a
  // segmentation fault printf("Attempting to access unmapped memory: %s\n",
  // (char *)addr); // DANGER!

  // Clean up the created file
  if (unlink(filepath) == -1) {
    perror("unlink");
    return 1;
  }

  return 0;
}

// open() and ftruncate():
// A file named "example.txt" is created and its size is set to accommodate the
// data to be written.

// mmap():
// The mmap() function maps the content of
// "example.txt" into the process's virtual address space. NULL as the first
// argument allows the kernel to choose a suitable address. file_size specifies
// the length of the mapping. PROT_READ | PROT_WRITE grants read and write
// permissions to the mapped memory. MAP_SHARED ensures that changes made to the
// mapped memory are written back to the underlying file and are visible to
// other processes mapping the same file.
// fd is the file descriptor of the file to be mapped.
// 0 is the offset within the file from where the mapping should start.

// strcpy():
// Data is written directly to the addr pointer, which points to the mapped
// memory region. This effectively writes to the "example.txt" file.

// munmap():
// The munmap() function is called to unmap the previously mapped memory region.
// addr is the starting address of the mapped region returned by mmap().
// file_size is the length of the region to be unmapped.
// Upon successful execution, the memory region is no longer accessible to the
// process. Subsequent attempts to access this memory will likely result in a
// SIGSEGV (segmentation fault).

// unlink():
// The created file "example.txt" is removed.