#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct Person {
  char* name;
  int age;
  int height;
  int weight;
};

struct Person * Person_create(char *name, int age, int weight, int height)
{
  struct Person *who = malloc(sizeof(struct Person));
  assert(who != NULL);

  who->name = strdup(name);
  who->age = age;
  who->height = height;
  who->weight = weight;

  return who;
}

void Person_destroy(struct Person *who)
{
  assert(who != NULL);
  free(who->name);
  free(who);
}

void Person_print(struct Person *who)
{
  assert(who != NULL);

  printf("Name: %s\n", who->name);
  printf("Age: %d\n", who->age);
  printf("Height: %d\n", who->height);
  printf("Weight: %d\n", who->weight);
}

int main(int argc, char* argv[]) {
  struct Person *joe = Person_create("Joe", 32, 160, 56);
  struct Person *mike = Person_create("mike", 30, 180, 60);

  printf("Mememory location of %s: %p\n", joe->name, joe);
  Person_print(joe);

  printf("Mememory location of %s: %p\n", mike->name, mike);
  Person_print(mike);

  joe->age += 20;
  joe->weight -= 20;
  joe->height -= 1;
  Person_print(joe);

  mike->age += 20;
  mike->weight += 40;
  mike->height -= 1;
  Person_print(mike);

  Person_destroy(mike);
  Person_destroy(joe);

  // Struct on Stack
  struct Person kyle;
  kyle.name = "Kyle";
  kyle.age = 23;
  kyle.weight = 195;
  kyle.height = 70;

  Person_print(&kyle);
  free(&kyle);
  return 0;
}
