#include <stdio.h>

/* This is a comment */
int main(int argc, char* argv[]) {

  int distance = 100;
  // This is also a comment
  printf("You are %d miles away.\n", distance);
  char *weekday = "Sunday";
  int month = 1;
  int day = 22;
  int hour = 11;
  int minute = 8;
  printf("The Date is: %s, %d, %d, %.2d:%.2d\n",
    weekday, month, day, hour, minute);
  printf("Hello world\n");
  printf("New for make\n");
  return 0;
}
