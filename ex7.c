#include <stdio.h>

int main(int argc, char* argv[]) {
  int distance = 100;
  float power = 2.345f;
  double superPower = 56789.4532;
  char initial = 'A';
  char firstName[] = "Kylw";
  char lastName[] = "Wilcox";

  printf("You are %d miles away\n", distance);
  printf("You have %f levels of power\n", power);
  printf("You have %f awesome super powers\n", superPower);
  printf("You have an initial: %c\n", initial);
  printf("I have the first name, %s", firstName);
  printf("I have the last name %s", lastName);
  printf("My whole name is %s %s\n", firstName, lastName);

  int bugs = 100;
  double bugRate = 1.2;
  printf("You have #%d bugs at a rate of %f\n", bugs, bugRate);
  long universeOfDefects = 1L * 1024L * 1L * 1024L;
  printf("The entire universe has %ld bugs.\n", universeOfDefects);

  double expectedBugs = bugs * bugRate;
  double partOfUni = expectedBugs / universeOfDefects;
  printf("You are expected to have %f bugs.\n", expectedBugs);
  printf("This is only a %e portion of the universe\n", partOfUni);

  char nulByte = '\0';
  int carePercent = bugs * nulByte;
  printf("Which means you should care this much %d%%\n", carePercent);
}
