#include "mergesort.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
  if (argc == 2 && strcmp(argv[1], "benchmark") == 0) {
    benchmark(100);
    benchmark(1000);
    benchmark(10000);
  } else {
    test(42);
  }
  return 0;
}
