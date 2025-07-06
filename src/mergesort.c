#include "mergesort.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void merge(int *arr, int left, int mid, int right) {
  // TODO: Implement standard iterative merge,
  // used by both parallel and serial sort functions.
}

void merge_sort_sequential(int *arr, int left, int right) {
  if (right - left <= 1)
    return;
  int mid = (left + right) / 2;
  merge_sort_sequential(arr, left, mid);
  merge_sort_sequential(arr, mid, right);
  merge(arr, left, mid, right);
}

void merge_sort_parallel_internal(int *arr, int left, int right) {
  // TODO: this is where the parallel algorithm needs to be implemented.
  // Best approach is to use `pragma omp task` and `pragma omp taskwait`
}

void merge_sort_parallel(int *arr, int left, int right) {

// NOTE: This part need not be modified, the parallel and single
// constructs creates the threads.
#pragma omp parallel
#pragma omp single
  {
    // the main sorting logic will be in this function.
    merge_sort_parallel_internal(arr, left, right);
  }
}
