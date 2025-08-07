#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

/// @brief
// lstat
/// Works exactly like the stat syscall, but if the file in question is a
/// symbolic link, information on the link is returned rather than its target.
/// int lstat(const char *path, struct stat *buf);
/// path – full path to file
/// buf – pointer to stat buffer (described in stat syscall)
/// Return data in buf is identical to the stat call.
/// @return
int main() {
  struct stat file_stat;
  const char *symlink_path = "example_link.txt";
  const char *target_path = "example.txt";

  // Create a dummy target file
  FILE *fp = fopen(target_path, "w");
  if (fp) {
    fprintf(fp, "This is a test file.\n");
    fclose(fp);
  } else {
    perror("fopen");
    return EXIT_FAILURE;
  }

  // Create a symbolic link to the target file
  if (symlink(target_path, symlink_path) == -1) {
    perror("symlink");
    return EXIT_FAILURE;
  }

  // Use lstat() to get info about the symbolic link
  if (lstat(symlink_path, &file_stat) == -1) {
    perror("lstat");
    return EXIT_FAILURE;
  }

  printf("Information about symbolic link '%s':\n", symlink_path);
  printf("File type: ");
  if (S_ISLNK(file_stat.st_mode)) {
    printf("Symbolic Link\n");
  } else {
    printf("Other\n");
  }
  printf("Size of link content (path length): %ld bytes\n",
         (long)file_stat.st_size);
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

  // Clean up
  unlink(symlink_path);
  // unlink(target_path);

  return EXIT_SUCCESS;
}