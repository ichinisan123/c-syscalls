#include <stdio.h>
#include <time.h>

int main() {
  time_t now1;
  time(&now1);
  printf("Current time1: %s", ctime(&now1));

  time_t now2 = time(NULL);
  printf("Current time2: %s", ctime(&now2));
  time_t now3 = time(&now3);
  printf("Current time3: %s", ctime(&now3));

  struct tm* t1 = localtime(&now1);
  printf("Year1: %d\n", t1->tm_year + 1900);
  struct tm* t2 = localtime(&now2);
  printf("Year2: %d\n", t2->tm_year + 1900);
  struct tm* t3 = localtime(&now3);
  printf("Year3: %d\n", t3->tm_year + 1900);

  char buffer[100];
  strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", t1);
  printf("Formatted time: %s\n", buffer);
  return 0;
}
