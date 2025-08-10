#include <asm-generic/ioctl.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define WR_VALUE _IOW('a', 'a', int32_t *)
#define RD_VALUE _IOR('a', 'b', int32_t *)

int main() {
  printf("WR_VALUE = 0x%08lX (%lu)\n", WR_VALUE, WR_VALUE);
  printf("RD_VALUE = 0x%08lX (%lu)\n", RD_VALUE, RD_VALUE);

  int fd;
  int32_t value, result;

  fd = open("/home/ichinisan/sa", O_RDWR);
  if (fd < 0) {
    perror("open");
    return 1;
  }

  value = 42;
  printf("Sending value %d to driver\n", value);
  ioctl(fd, WR_VALUE, &value);

  printf("Reading value from driver\n");
  ioctl(fd, RD_VALUE, &result);
  printf("Got value: %d\n", result);

  close(fd);
  return 0;
}
