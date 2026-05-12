#include "instructions.h"
#include <stdio.h>

void print_working(float num1, float num2, float ans, int matFunc) {
  switch (matFunc) {
  case 1:
    printf("Added %g and %g to get %g\n", num1, num2, ans);
    break;
  case 2:
    printf("Subtracted %g from %g to get %g\n", num2, num1, ans);
    break;
  case 3:
    printf("Multiplied %g and %g to get %g\n", num1, num2, ans);
    break;
  case 4:
    printf("Divided %g by %g to get %g\n", num1, num2, ans);
    break;
  case 5:
    printf("%g to the power of %g got %g\n", num1, num2, ans);
    break;
  default:
    printf("No working for this step defined");
  }
}
