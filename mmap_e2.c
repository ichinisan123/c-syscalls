#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

// compile and run
// example.txt: hello world
// gcc mmap_e2.c && ./a.out example.txt
int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("File path not mentioned\n");
    exit(0);
  }

  const char *filepath = argv[1];
  int fd = open(filepath, O_RDWR);
  printf("File descriptor: %d\n", fd);
  if (fd < 0) {
    printf("\n\"%s \" could not open\n", filepath);
    exit(1);
  }

  struct stat statbuf;
  int err = fstat(fd, &statbuf);
  if (err < 0) {
    printf("\n\"%s \" could not open\n", filepath);
    exit(2);
  }

  char *ptr =
      mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (ptr == MAP_FAILED) {
    printf("Mapping Failed\n");
    return 1;
  }
  printf("Mapped content: %s\n", ptr);
  printf("Mapped size: %ld\n", statbuf.st_size);
  close(fd);

  ptr[statbuf.st_size - 2] = '@';
  ssize_t n = write(1, ptr, statbuf.st_size);
  if (n != statbuf.st_size) {
    printf("Write failed\n");
  }
  while (1);
}