#include <stdarg.h>
#include <stdio.h>

void show_addresses(int a, int b, ...) {
  printf("Address of a: %p\n", (void*)&a);
  printf("Address of b: %p\n", (void*)&b);

  va_list args;
  va_start(args, b);

  // On simple architectures, args would point right after b
  printf("va_list points to: %p\n", (void*)args);

  // Show first few variadic arguments
  printf("First var arg: %d at %p\n", va_arg(args, int), (void*)args);
  printf("Second var arg: %d at %p\n", va_arg(args, int), (void*)args);

  va_end(args);
}

int main() {
  show_addresses(10, 20, 30, 40, 50);
  return 0;
}
