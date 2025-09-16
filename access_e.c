#include <stdio.h>   // Required for printf()
#include <unistd.h>  // Required for access()


// access
// Check permissions of current user for a specified file or device.

// int access(const char *pathname, int mode)
// pathname – file or device
// mode – permissions check to perform
// Returns zero on success.
int main() {
  const char *filepath = "example.txt";  // Path to the file to check

  // Create a dummy file for demonstration if it doesn't exist
  FILE *fp = fopen(filepath, "w");
  if (fp != NULL) {
    fprintf(fp, "This is a test file.\n");
    fclose(fp);
  }

  // Check for existence (F_OK)
  if (access(filepath, F_OK) == 0) {
    printf("File '%s' exists.\n", filepath);
  } else {
    printf("File '%s' does not exist.\n", filepath);
  }

  // Check for read permission (R_OK)
  if (access(filepath, R_OK) == 0) {
    printf("You have read access to '%s'.\n", filepath);
  } else {
    printf("You do NOT have read access to '%s'.\n", filepath);
  }

  // Check for write permission (W_OK)
  if (access(filepath, W_OK) == 0) {
    printf("You have write access to '%s'.\n", filepath);
  } else {
    printf("You do NOT have write access to '%s'.\n", filepath);
  }

  // Check for execute/search permission (X_OK) - more relevant for directories
  // For a regular file, it checks if it's executable
  if (access(filepath, X_OK) == 0) {
    printf("You have execute/search access to '%s'.\n", filepath);
  } else {
    printf("You do NOT have execute/search access to '%s'.\n", filepath);
  }

  return 0;
}