#include <stdio.h>

int main(int argc, char *argv[]) {
  // Create two arrays
  int ages[] = { 10, 20, 30, 40 , 50};
  char *names[] = { "Alan", "Frank", "Mary", "John", "Lisa" };

  // Safely Count the size of ages
  int count = sizeof(ages) / sizeof(int);
  int i = 0;

  // First way to iterate through arrays

  for(i = 0; i < count; i++) {
    printf("%s has %d years alive.\n", names[i], ages[i]);
  }

  printf("----\n");
  // Second way to iterate using pointers
  int *cur_age = ages;
  char **cur_names = names;
  for(i = 0; i < count; i++) {
    printf("%s has %d years alive.\n", *(cur_names + i), *(cur_age + i));
  }

  printf("---\n");

  // Third way using pointers as arrays

  for(i = 0; i < count; i++) {
    printf("%s has %d years alive.\n", cur_names[i], cur_age[i]);
  }

  printf("---\n");

  // fourth way in a complex way

  for(cur_names = names, cur_age = ages;
    (cur_age - ages) < count; // Check will go like 10 - 10, 11 - 10, 12 - 10
    cur_names++, cur_age++) {
      printf("%s has %d years alive.\n", *cur_names, *cur_age);
    }

  return 0;
}
