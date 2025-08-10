#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define WR_VALUE _IOW('a', 'a', int32_t *)
#define RD_VALUE _IOR('a', 'b', int32_t *)

// ioctl
// Set parameters of device files.

// int ioctl(int d, int request, ...)
// d – open file descriptor the device file
// request – request code
// ... – untyped pointer
// Returns zero upon success in most cases.

int main() {
  int fileDescriptor;
  int32_t val, num;
  printf("opening the driver\n");
  fileDescriptor = open("/dev/random", O_RDWR);

  if (fileDescriptor < 0) {
    perror("Failed to open the device");
    return EXIT_FAILURE;
  }

  printf("enter the value that you want to send\n");
  scanf("%d", &num);
  printf("writing the value to the driver\n");
  ioctl(fileDescriptor, WR_VALUE, (int32_t *)&num);

  printf("reading the value from the driver\n");
  ioctl(fileDescriptor, RD_VALUE, (int32_t *)&val);
  printf("Read value: %d\n", val);

  printf("closing the driver\n");
  close(fileDescriptor);
  return 0;
}

// 1. Background: ioctl commands
// In Linux, ioctl() (input/output control) is a system call used to send
// device-specific control commands from user space to a device driver in kernel
// space. Commands are usually defined using helper macros like:

// _IO → no data transfer
// _IOR → read: kernel → user space
// _IOW → write: user space → kernel
// _IOWR → read/write both directions

// The macro arguments are:
// _IOX(type, number, data_type)
// type — a magic number (character) that uniquely identifies your device class
// (often 'a', 'b', 'M', etc.).
// number — a command number (different for each operation).
// data_type — the type of the data being passed.

// 2. Your definitions

// #define WR_VALUE _IOW('a', 'a', int32_t *)
// #define RD_VALUE _IOR('a', 'b', int32_t *)

// First one: WR_VALUE
// _IOW → Write: the user space program sends data to the kernel.
// 'a' → magic number for your device.
// 'a' → command number (yes, can be a char literal; internally it's an
// integer).
// int32_t * → the type of data pointer being passed.
// Effectively:
// "A command that sends a 32-bit integer from user space to the kernel."

// Second one: RD_VALUE
// _IOR → Read: the kernel sends data to the user space program.
// 'a' → magic number.
// 'b' → command number (different from above).
// int32_t * → type of data being read.
// Effectively:
// "A command that retrieves a 32-bit integer from the kernel to user space."

