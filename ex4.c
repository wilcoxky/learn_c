#include <stdio.h>

int main(int argc, char* argv[]) {
  int age = 10;
  int height = 520;

  printf("You are %d years old\n", age);
  printf("You are %x tall\n", height);
  return 0;
}


// x += 10 === x = x + 10
// so x >>= 3 === x = x >> 3 === x = x * 2 ^ 3
