#include <stdio.h>   // Required for printf(), fopen(), fprintf(), fclose()
#include <unistd.h>  // Required for access()

/*
 * access() - Check user permissions for a file
 *
 * int access(const char *pathname, int mode)
 *
 * pathname: Path to file or directory
 * mode: Permission flags to check (F_OK, R_OK, W_OK, X_OK)
 *       - F_OK: Test for existence
 *       - R_OK: Test for read permission
 *       - W_OK: Test for write permission
 *       - X_OK: Test for execute permission
 *
 * Returns: 0 on success, -1 on failure (sets errno)
 *
 * Note: access() checks permissions using the real user ID, not the
 * effective user ID. This can differ in setuid programs.
 */

//  gcc -o access_demo access_demo.c
// ./access_demo

int main(void) {
  const char* filepath = "example.txt";

  // Create a test file if it doesn't exist
  FILE* fp = fopen(filepath, "w");
  if (fp == NULL) {
    perror("Error creating file");
    return 1;
  }
  fprintf(fp, "This is a test file.\n");
  fclose(fp);

  printf("Checking permissions for '%s':\n", filepath);
  printf("=====================================\n");

  // Check for existence (F_OK)
  if (access(filepath, F_OK) == 0) {
    printf("✓ File exists\n");
  } else {
    perror("✗ File does not exist");
    return 1;  // Exit if file doesn't exist
  }

  // Check for read permission (R_OK)
  if (access(filepath, R_OK) == 0) {
    printf("✓ Read permission granted\n");
  } else {
    perror("✗ Read permission denied");
  }

  // Check for write permission (W_OK)
  if (access(filepath, W_OK) == 0) {
    printf("✓ Write permission granted\n");
  } else {
    perror("✗ Write permission denied");
  }

  // Check for execute permission (X_OK)
  // Note: For regular files, this checks if the file is executable
  // For directories, this checks if you can search/traverse the directory
  if (access(filepath, X_OK) == 0) {
    printf("✓ Execute permission granted\n");
  } else {
    // This is expected for regular text files
    printf("✗ Execute permission denied (expected for text files)\n");
  }

  // Bonus: Check multiple permissions at once
  if (access(filepath, R_OK | W_OK) == 0) {
    printf("\n✓ Both read AND write permissions granted\n");
  } else {
    printf("\n✗ Missing read or write permission\n");
  }

  return 0;
}

