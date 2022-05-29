#include <stdio.h>
#include <stdlib.h>

#include "calculator.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    dprintf(2, "Usage: bintree-calculator EXPRESSION\n");
    exit(EXIT_FAILURE);
  }
  
  double result = calculate(argv[1]);
  printf("%s = %f\n", argv[1], result);
  
  return 0;
}
