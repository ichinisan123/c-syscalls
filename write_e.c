#include <unistd.h>  // Required for the write() system call

/// @brief
/// write
/// Writes to a specified file using a file descriptor.
/// Before using this call, you must first obtain a file
/// descriptor using the open syscall.
/// Returns bytes written successfully.

/// ssize_t write(int fd, const void *buf, size_t count)

/// fd - file descriptor
/// buf - pointer to the buffer to write
/// count - number of bytes to write
/// @return number of bytes written on success, -1 on error
int main() {
  char message[] = "Hello, System Call!\n";
  // write(file_descriptor, buffer, count)
  // 1 is the file descriptor for standard output (stdout)
  // message is the buffer containing the data to write
  // sizeof(message) - 1 calculates the length of the string, excluding the null
  // terminator
  write(1, message, sizeof(message) - 1);
  return 0;
}

// The primary difference between write() and printf() in C lies in their
// level of abstraction and functionality:

// write():
// This is a system call that
// directly interacts with the operating system kernel to write raw bytes to a
// file descriptor. It operates at a lower level, providing direct control over
// the data transfer to an output device (like the console or a file). write()
// does not perform any formatting or interpretation of the data; it simply
// writes the specified number of bytes as-is.

// printf():
// This is a standard
// library function that provides high-level formatted output. printf() takes a
// format string and a variable number of arguments, interpreting the format
// specifiers (e.g., %d, %s, %f) to convert and format the data into a sequence
// of characters. Internally, printf() typically uses the write() system call to
// actually send the formatted output to the standard output stream (stdout),
// which is usually the console. It often employs buffering to optimize output
// operations, flushing the buffer when it's full or when a newline character
// (\n) is encountered. In essence: printf() builds upon write(). While write()
// is for raw byte transfer, printf() adds a layer of convenience and power for
// formatting and presenting various data types in a human-readable way.
