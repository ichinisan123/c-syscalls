#include <stdio.h>
int main() {
  printf("--- check sizeof ---/n");
  size_t sizeChar = sizeof(char);
  printf("Size of char: %zu bytes\n", sizeChar);
  size_t sizeShort = sizeof(short);
  printf("Size of short: %zu bytes\n", sizeShort);
  size_t sizeInt = sizeof(int);
  printf("Size of int: %zu bytes\n", sizeInt);
  size_t sizeLong = sizeof(long);
  printf("Size of long: %zu bytes\n", sizeLong);
  size_t sizeLongLong = sizeof(long long);
  printf("Size of long long: %zu bytes\n", sizeLongLong);

  size_t sizeFloat = sizeof(float);
  printf("Size of float: %zu bytes\n", sizeFloat);
  size_t sizeDouble = sizeof(double);
  printf("Size of double: %zu bytes\n", sizeDouble);

  size_t sizeVoidPtr = sizeof(void*);
  printf("Size of void*: %zu bytes\n", sizeVoidPtr);
  size_t sizeSizeT = sizeof(size_t);
  printf("Size of size_t: %zu bytes\n", sizeSizeT);
  size_t sizeIntPtr = sizeof(int*);
  printf("Size of int*: %zu bytes\n", sizeIntPtr);
  size_t sizeFloatPtr = sizeof(float*);
  printf("Size of float*: %zu bytes\n", sizeFloatPtr);
  size_t sizeDoublePtr = sizeof(double*);
  printf("Size of double*: %zu bytes\n", sizeDoublePtr);
  size_t sizeCharPtr = sizeof(char*);
  printf("Size of char*: %zu bytes\n", sizeCharPtr);
  size_t sizeLongPtr = sizeof(long*);
  printf("Size of long*: %zu bytes\n", sizeLongPtr);
  size_t sizeShortPtr = sizeof(short*);
  printf("Size of short*: %zu bytes\n", sizeShortPtr);
  size_t sizeLongLongPtr = sizeof(long long*);
  printf("Size of long long*: %zu bytes\n", sizeLongLongPtr);
  size_t sizeVoid = sizeof(void);
  printf("Size of void: %zu bytes\n", sizeVoid);
  size_t sizeFuncPtr = sizeof(void (*)());
  printf("Size of function pointer: %zu bytes\n", sizeFuncPtr);
  size_t sizeStruct = sizeof(struct {
    int a;
    float b;
  });
  printf("Size of struct: %zu bytes\n", sizeStruct);
  size_t sizeUnion = sizeof(union {
    int a;
    float b;
  });
  printf("Size of union: %zu bytes\n", sizeUnion);
  size_t sizeEnum = sizeof(enum {RED, GREEN, BLUE});
  printf("Size of enum: %zu bytes\n", sizeEnum);
  size_t sizeBitField = sizeof(struct {
    unsigned int a : 1;
    unsigned int b : 2;
  });
  printf("Size of bit-field struct: %zu bytes\n", sizeBitField);
  size_t sizeComplex = sizeof(double _Complex);
  printf("Size of double _Complex: %zu bytes\n", sizeComplex);
  size_t sizeAtomic = sizeof(_Atomic int);
  printf("Size of _Atomic int: %zu bytes\n", sizeAtomic);
  size_t sizeNullPtr = sizeof(NULL);
  printf("Size of NULL: %zu bytes\n", sizeNullPtr);
  size_t sizeBool = sizeof(_Bool);
  printf("Size of _Bool: %zu bytes\n", sizeBool);
  size_t sizeLongDouble = sizeof(long double);
  printf("Size of long double: %zu bytes\n", sizeLongDouble);
  size_t sizeFunction = sizeof(int());
  printf("Size of function: %zu bytes\n", sizeFunction);
  size_t sizePointerToFunction = sizeof(int (*)());
  printf("Size of pointer to function: %zu bytes\n", sizePointerToFunction);
  size_t sizeVolatileInt = sizeof(volatile int);
  printf("Size of volatile int: %zu bytes\n", sizeVolatileInt);
  size_t sizeByte = sizeof(unsigned char);
  printf("Size of unsigned char: %zu bytes\n", sizeByte);

  int* ptrInt;
  size_t sizePtrInt = sizeof(ptrInt);
  printf("Size of int*: %zu bytes\n", sizePtrInt);
  size_t sizePtrIntValue = sizeof(*ptrInt);
  printf("Size of *int*: %zu bytes\n", sizePtrIntValue);

  long* ptrLong;
  size_t sizePtrLong = sizeof(ptrLong);
  printf("Size of long*: %zu bytes\n", sizePtrLong);
  size_t sizePtrLongValue = sizeof(*ptrLong);
  printf("Size of *long*: %zu bytes\n", sizePtrLongValue);

  return 0;
}
