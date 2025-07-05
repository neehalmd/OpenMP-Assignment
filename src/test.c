#include "mergesort.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TEST_SIZE 10

bool check_sorted(int *arr, int size) {
  for (int i = 1; i < size; i++) {
    if (arr[i] < arr[i - 1]) {
      return false;
    }
  }
  return true;
}

void print_array(const int *arr, int size) {
  printf("[");
  for (int i = 0; i < size - 1; i++)
    printf("%d ", arr[i]);
  printf("%d]\n", arr[size - 1]);
}

void test(int seed) {
  printf("[ INFO ] Running test() with small array (%d elements):\n",
         TEST_SIZE);

  // constructing array for tests
  int serial_arr[TEST_SIZE], parallel_arr[TEST_SIZE];
  srand(42);
  for (int i = 0; i < TEST_SIZE; i++) {
    int v = rand() % 100;
    serial_arr[i] = parallel_arr[i] = v;
  }

#ifdef DEBUG
  printf("[ DEBUG ] Original:\t\t");
  print_array(serial_arr, TEST_SIZE);
#endif

  // NOTE: Serial Test
  merge_sort_sequential(serial_arr, 0, TEST_SIZE);

  if (check_sorted(serial_arr, TEST_SIZE)) {
    printf("[ SUCCESS ] Serial Sort Verified");
  } else {
    printf("[ FAIL ] Serial Array was not sorted\n");
  }
#ifdef DEBUG
  printf("[ DEBUG ] Serial Sort:\t\t");
  print_array(serial_arr, TEST_SIZE);
#endif

  // NOTE: Parallel Test
  merge_sort_parallel(parallel_arr, 0, TEST_SIZE);

  if (check_sorted(parallel_arr, TEST_SIZE)) {
    printf("[ SUCCESS ] Parallel Sort Verified\n");
  } else {
    printf("[ FAIL ] Parallel Array was not sorted\n");
  }

#ifdef DEBUG
  printf("[ DEBUG ] Parallel Sort:\t");
  print_array(serial_arr, TEST_SIZE);
#endif
}

void benchmark(int size) {
  printf("[ INFO ] Running benchmark() with large array (%d elements)...\n",
         size);
  int *serial_arr = malloc(size * sizeof(int));
  int *parallel_arr = malloc(size * sizeof(int));
  if (!serial_arr || !parallel_arr) {
    printf("[ ERROR ] Memory allocation failed\n");
    exit(1);
  }

  srand(42);
  for (int i = 0; i < size; i++) {
    int v = rand();
    serial_arr[i] = parallel_arr[i] = v;
  }

  clock_t t0 = clock();
  merge_sort_sequential(serial_arr, 0, size);
  clock_t t1 = clock();

  clock_t t2 = clock();
  merge_sort_parallel(parallel_arr, 0, size);
  clock_t t3 = clock();

  double t_seq = (double)(t1 - t0) / CLOCKS_PER_SEC;
  double t_par = (double)(t3 - t2) / CLOCKS_PER_SEC;

  printf("[ INFO ] Sequential time: %.4fs\n", t_seq);
  printf("[ INFO ] Parallel time:   %.4fs\n", t_par);

  if (check_sorted(serial_arr, size) && check_sorted(parallel_arr, size))
    printf("[ SUCCESS ] Arrays match — Speedup: %.2fx\n", t_seq / t_par);
  else
    printf("[ FAIL ] Arrays are Not Sorted\n");

  free(serial_arr);
  free(parallel_arr);
}
