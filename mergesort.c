#include "mergesort.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void merge(int *arr, int left, int mid, int right) {
  // TODO: Implement Merge function(serial)
  // will be used by both sequential and parallel
  // implementations.
}
void merge_sort_sequential(int *arr, int left, int right) {
  if (right - left <= 1)
    return;
  int mid = (left + right) / 2;
  merge_sort_sequential(arr, left, mid);
  merge_sort_sequential(arr, mid, right);
  merge(arr, left, mid, right);
}

void merge_sort_parallel(int *arr, int left, int right) {
  // TODO: Implement Merge Sort using Open MP
  // each recursive call will be run parallel
}
