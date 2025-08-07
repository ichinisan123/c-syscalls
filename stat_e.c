#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>  // For stat() and ctime()

/// @brief
/// stat
/// Returns information about a file in a structure named stat.
/// int stat(const char *path, struct stat *buf);
/// path - pointer to the name of the file
/// buf - pointer to the structure to receive file information
/// @return
int main() {
  struct stat file_stat;
  const char *filename = "example.txt";

  if (stat(filename, &file_stat) == 0) {
    printf("File: %s\n", filename);
    printf("Size: %lld bytes\n", (long long)file_stat.st_size);
    printf("Permissions: %o\n",
           file_stat.st_mode & 0777);  // Last 3 octal digits for permissions
    printf("Last modified: %s", ctime(&file_stat.st_mtime));
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

  } else {
    perror("Error calling stat()");
  }

  return 0;
}