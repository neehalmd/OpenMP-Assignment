#include "mergesort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TEST_SIZE 10

void print_array(const int *arr, int size) {
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

void test(int seed) {
  printf("[ INFO ] Running test() with small array (%d elements):\n",
         TEST_SIZE);

  int a[TEST_SIZE], b[TEST_SIZE];
  srand(42);
  for (int i = 0; i < TEST_SIZE; i++) {
    int v = rand() % 100;
    a[i] = b[i] = v;
  }

#ifdef DEBUG
  printf("Original:\n");
  print_array(a, TEST_SIZE);
#endif

  merge_sort_sequential(a, 0, TEST_SIZE);
  merge_sort_parallel(b, 0, TEST_SIZE);

#ifdef DEBUG
  printf("[ DEBUG ] Sorted (sequential):\n");
  print_array(a, TEST_SIZE);
  printf("[ DEBUG ] Sorted (parallel):\n");
  print_array(b, TEST_SIZE);
#endif

  for (int i = 0; i < TEST_SIZE; i++) {
    if (a[i] != b[i]) {
      printf("[ ERROR ] Mismatch at index %d: %d != %d\n", i, a[i], b[i]);
      return;
    }
  }
  printf("[ SUCCESS ] Arrays match\n");
}

void benchmark(int size) {
  printf("[ INFO ] Running benchmark() with large array (%d elements)...\n",
         size);
  int *a = malloc(size * sizeof(int));
  int *b = malloc(size * sizeof(int));
  if (!a || !b) {
    printf("[ ERROR ] Memory allocation failed\n");
    exit(1);
  }

  srand(42);
  for (int i = 0; i < size; i++) {
    int v = rand();
    a[i] = b[i] = v;
  }

  clock_t t0 = clock();
  merge_sort_sequential(a, 0, size);
  clock_t t1 = clock();

  clock_t t2 = clock();
  merge_sort_parallel(b, 0, size);
  clock_t t3 = clock();

  double t_seq = (double)(t1 - t0) / CLOCKS_PER_SEC;
  double t_par = (double)(t3 - t2) / CLOCKS_PER_SEC;

  printf("[ INFO ] Sequential time: %.4fs\n", t_seq);
  printf("[ INFO ] Parallel time:   %.4fs\n", t_par);

  int ok = 1;
  for (int i = 0; i < size; i++) {
    if (a[i] != b[i]) {
      printf("[ ERROR ] Mismatch at index %d\n", i);
      ok = 0;
      break;
    }
  }

  if (ok)
    printf("[ SUCCESS ] Arrays match — Speedup: %.2fx\n", t_seq / t_par);
  else
    printf("[ FAIL ] Arrays do not match\n");

  free(a);
  free(b);
}
