#include <fcntl.h>  // For open()
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

/// @brief
/// fstat
/// Works exactly like the stat syscall except a file descriptor (fd) is
/// provided instead of a path.
/// int fstat(int fd, struct stat *buf);
/// fd – file descriptor
/// buf – pointer to stat buffer (described in stat syscall)
/// Return data in buf is identical to the stat call.
/// @return 0 on success, -1 on error
int main() {
  int fd;
  struct stat file_stat;

  // Open a file (e.g., "example.txt")
  fd = open("example.txt", O_RDONLY);
  if (fd == -1) {
    perror("Error opening file");
    return 1;
  }

  // Get file information using fstat()
  if (fstat(fd, &file_stat) == -1) {
    perror("Error getting file info");
    close(fd);
    return 1;
  }

  // Print some file information
  printf("File size: %lld bytes\n", (long long)file_stat.st_size);
  // Octal representation of permissions
  printf("File permissions: %o\n", file_stat.st_mode & 0777);

  printf("--------------------\n");
  // st_dev: ID of device containing the file.
  printf("st_dev : %ld\n", file_stat.st_dev);
  // st_ino: Inode number (unique identifier within a file system).
  printf("st_ino : %ld\n", file_stat.st_ino);
  // st_mode: File type and permissions (e.g., regular file, directory,
  // symbolic link, read/write/execute permissions).
  printf("st_mode : %u\n", file_stat.st_mode);
  // st_nlink: Number of hard links to the file.
  printf("st_nlink : %ld\n", file_stat.st_nlink);
  // st_uid: User ID of the owner.
  printf("st_uid : %d\n", file_stat.st_uid);
  // st_gid: Group ID of the owner.
  printf("st_gid : %d\n", file_stat.st_gid);
  // device ID (only if device file)
  printf("st_rdev : %lu\n", file_stat.st_rdev);
  // st_size: Total size of the file in bytes.
  printf("st_size : %ld\n", file_stat.st_size);
  // st_blksize: Block size for file system I/O.
  printf("st_blksize : %ld\n", file_stat.st_blksize);
  // st_blocks: Number of 512B blocks allocated.
  printf("st_blocks : %ld\n", file_stat.st_blocks);
  // st_atime: Time of last access.
  printf("st_atime : %s\n", ctime(&file_stat.st_atime));
  // st_mtime: Time of last modification.
  printf("st_mtime : %s\n", ctime(&file_stat.st_mtime));
  // st_ctime: Time of last status change.
  printf("st_ctime : %s\n", ctime(&file_stat.st_ctime));

  // Close the file
  close(fd);

  return 0;
}