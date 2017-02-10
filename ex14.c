#include <stdio.h>
#include <ctype.h>

// forward declarations
int can_it_print(char charzard);
void print_letters(char arg[]);
void print_arguments(int argc, char* argv[]);

void print_arguments(int argc, char* argv[]) {
  int i = 0;

  for(i = 1; i < argc; i++) {
    print_letters(argv[i]);
  }
}

void print_letters(char arg[]) {
  int i = 0;

  for(i = 0; arg[i] != '\0'; i++) {
    char ch = arg[i];
    if (can_it_print(ch)) {
      printf("'%c' == %d ", ch, ch);
    }
  }
  printf("\n");
}

int can_it_print(char charzard) {
  return isalpha((int)charzard) || isblank((int)charzard);
}

int main(int argc, char* argv[]) {
  print_arguments(argc, argv);
  return 0;
}
