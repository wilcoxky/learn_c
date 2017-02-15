#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>

// What would be my header.h file

typedef int (*compare_func)(int a, int b);
typedef int *(*sort_func)(int *numbers, int count, compare_func compare_f);

void die(const char *mesage);
int *bubble_sort(int *numbers, int count, compare_func compare_f);
int *merge_sort(int *numbers, int count, compare_func compare_f);
void merge(int *target, int *left, int *right, int leftCount, int rightCount, compare_func compare_fn);

/** old friend from ex17 */
void die(const char *message) {
  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }
  exit(1);
}


/**
 * Classic bubble sort that uses whatever
 * compare function it is given
 * NOTE: Good to remember that bubble sort mallocs space on heap
 */
int *bubble_sort(int *numbers, int count, compare_func compare_f)
{
  int i = 0;
  int j = 0;
  int temp = 0;
  int *target = malloc(sizeof(int) * count);

  if (!target) {
    die("Mememory Error");
  }
  // Copy Array to target using memcpy
  memcpy(target, numbers, sizeof(int) * count);

  // I had a error when i did this because i was accessing j = count + 1 => doesnt exist!
  for (i = 0; i < count; i++) {
    for (j = 0; j < count - 1; j++) {
      if (compare_f(target[j], target[j+1]) > 0) {
        temp = target[j+1];
        target[j+1] = target[j];
        target[j] = temp;
      }
    }
  }
  return target;
}

int *merge_sort(int *numbers, int count, compare_func compare_f)
{
  int *target = malloc(sizeof(int) * count);
  memcpy(target, numbers, sizeof(int) * count);

  if (!target) {
    die("Mememory Error");
  }

  if (count < 2) {
    return target;
  }

  int leftCount = count / 2;
  int rightCount = count - leftCount;
  int *leftHalf = malloc(sizeof(int) * leftCount);
  int *rightHalf = malloc(sizeof(int) * rightCount);
  int i = 0;
  // Split the target into left and right
  for (i = 0; i < leftCount; i++) {
    leftHalf[i] = target[i];
  }

  for (i = leftCount; i < count; i++) {
    rightHalf[i-leftCount] = target[i];
  }

  int *leftSorted = merge_sort(leftHalf, leftCount, compare_f);
  int *rightSorted = merge_sort(rightHalf, rightCount, compare_f);

  merge(target, leftSorted, rightSorted, leftCount, rightCount, compare_f);
  // Free up used mem, this also frees the targets that are created as
  // we merge since leftHalf and right half are continually combined and then freed
  free(leftHalf);
  free(rightHalf);
  free(leftSorted);
  free(rightSorted);
  return target;
}

void merge(int* target, int *left, int *right, int leftCount, int rightCount, compare_func compare_fn)
{
  // int *target = malloc(sizeof(int) * (leftCount + rightCount));
  int i = 0; // Left hand side pointer
  int j = 0; // Right hand side pointer
  int k = 0; // target pointer

  if (!target) {
    die("Memeory Error");
  }
  // Go through until one of them is at the count
  while (i < leftCount && j < rightCount) {
    if (compare_fn(left[i], right[j]) > 0) {
      target[k] = right[j];
      j++;
    } else {
      target[k] = left[i];
      i++;
    }
    k++;
  }
  // Add on remaining
  while(i < leftCount) {
    target[k] = left[i];
    k++;
    i++;
  }

  // Add on remaining
  while(j < rightCount) {
    target[k] = right[j];
    k++;
    j++;
  }
}

int sorted_order(int a, int b)
{
  // a > b returns 1 if greater 0 if not
  // a < b return 1 if less than 0 if not
  // Basically if a > will return 1
  return (a > b) - (a < b);
}

int reverse_order(int a, int b)
{
  return (a < b) - (a > b);
}

int random_order(int a, int b)
{
  if (a == 0 || b == 0) {
    return 0;
  } else {
    return a % b;
  }
}

double breaking_func(int a, int b)
{
  return (double)a;
}
/**
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out
 * NOTE: We are clearing the space on the heap that
 * is used by bubble_sort
 */

void test_sorting(int *numbers, int count, sort_func sort_f, compare_func fn)
{
  int *sorted = sort_f(numbers, count, fn);
  int i = 0;
  for (i = 0; i < count; i++) {
    if (i + 1 == count) {
      printf("%d]", sorted[i]);
    } else if (i == 0) {
      printf("[%d, ", sorted[i]);
    } else {
      printf("%d, ", sorted[i]);
    }

  }

  printf("\n");

  free(sorted);
}

int main(int argc, char *argv[])
{
  if (argc < 2) {
    die("Usage: ex18 4 3 1 5 6");
  }

  int count = argc - 1;
  char **inputs = argv + 1; // Distinguish inputs
  int i = 0; // Declare i early
  int *numbers = malloc(sizeof(int) * count);

  // Parse args into ints
  for (i = 0; i < count; i++) {
    numbers[i] = atoi(inputs[i]);
  }
  printf("-----MERGE SORT-----\n");
  clock_t start = clock(), diff;
  test_sorting(numbers, count, merge_sort, sorted_order);
  test_sorting(numbers, count, merge_sort, reverse_order);
  test_sorting(numbers, count, merge_sort, random_order);
  diff = clock() - start;
  double msec = diff * 1000 / (double)CLOCKS_PER_SEC;
  printf("Time taken %f seconds %f milliseconds\n", msec/1000, msec);
  printf("-----END-----\n\n");

  printf("-----BUBBLE SORT-----\n");
  start = clock();
  test_sorting(numbers, count, bubble_sort, sorted_order);
  test_sorting(numbers, count, bubble_sort, reverse_order);
  test_sorting(numbers, count, bubble_sort, random_order);
  diff = clock() - start;
  msec = diff * 1000 / (double)CLOCKS_PER_SEC;
  printf("Time taken %f seconds %f milliseconds\n", msec/1000, msec);
  printf("-----END-----\n");
  // test_sorting(numbers, count, breaking_func);

  free(numbers);

  return 0;
}
