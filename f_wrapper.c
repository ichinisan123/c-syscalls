#include <stdio.h>
#include <stdlib.h>

// Example of a Wrapper Function in C:
// Consider a scenario where you frequently use malloc and free for memory
// management, but you want to add error checking to malloc and perhaps some
// logging.

// Original function (standard library function in this case)
// void *malloc(size_t size);
// Wrapper function for malloc
void *safe_malloc(size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    fprintf(stderr, "Error: Memory allocation failed for size %zu\n", size);
    // You could also exit, throw an error, or handle it differently
    exit(EXIT_FAILURE);
  }
  printf("Successfully allocated %zu bytes of memory.\n", size);
  return ptr;
}

// Wrapper function for free (optional, for consistency or logging)
void safe_free(void *ptr) {
  if (ptr != NULL) {
    free(ptr);
    printf("Successfully freed memory at address %p.\n", ptr);
  } else {
    printf("Attempted to free a NULL pointer.\n");
  }
}

int main() {
  int *my_array;

  // Using the wrapper function
  my_array = (int *)safe_malloc(5 * sizeof(int));

  // Use my_array...
  for (int i = 0; i < 5; i++) {
    my_array[i] = i * 10;
    printf("%d ", my_array[i]);
  }
  printf("\n");

  // Using the wrapper function to free
  safe_free(my_array);

  // Example of a failed allocation (if you were to test large sizes)
  // int *large_array = (int *)safe_malloc(1000000000000UL * sizeof(int));

  printf("test: my_array[0] after free: %d\n", my_array[0]);

  return 0;
}

// In this example, safe_malloc and safe_free act as wrapper functions for the
// standard library's malloc and free. safe_malloc adds error checking and a
// success message, while safe_free adds a message and handles NULL pointers
// gracefully. This demonstrates how wrappers can enhance or modify the behavior
// of existing functions without directly altering their original
// implementations.
