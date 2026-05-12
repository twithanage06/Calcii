/*
 AUTHOR/S: THANUJA A.W
 DATE: 12/05/2026
 VERSION: 0.1.0
 */
#include "matfunc.h"
#include "instructions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
float add(float a, float b) {
  float ans = a + b;
  print_working(a, b, ans, 1);
  return ans;
}
float sub(float a, float b) {
  float ans = a - b;
  print_working(a, b, ans, 2);
  return ans;
}
float mul(float a, float b) {
  float ans = a * b;
  print_working(a, b, ans, 3);
  return ans;
}
float divide(float a, float b) {
  float ans = a / b;
  print_working(a, b, ans, 4);
  return ans;
}
float power(float a, int b) {
  int i = 1;
  float product = a;
  while (i < b) {
    product = product * a;
    i++;
  }
  print_working(a, (float)b, product, 5);
  return product;
}
char *bodmas(char *input_equation) {
  char *eq = strdup(input_equation);
  if (eq == NULL) {
    return NULL;
  }
  float ans;
  int i = 0;
  int j = 0;
  int l = 0;
  while (strchr(eq, '(')) {
    int start = 0;
    int end = 0;
    for (int k = 0; k < strlen(eq); k++) {
      if (eq[k] == '(') {
        start = k;
      } else if (eq[k] == ')') {
        end = k;
        break;
      }
    }

    int insideBracketRange = end - start - 1;
    char *interBracketEq = malloc(insideBracketRange + 1);
    strncpy(interBracketEq, &eq[start + 1], insideBracketRange);
    interBracketEq[insideBracketRange] = '\0';

    char *interAns = bodmas(interBracketEq);
    int ansLen = strlen(interAns);
    memmove(&eq[start + ansLen], &eq[end + 1], strlen(&eq[end + 1]) + 1);
    memcpy(&eq[start], interAns, ansLen);

    free(interBracketEq);
    free(interAns);
  }
  while (l < strlen(eq)) {
    char tempResult[32];
    if (eq[l] == '^') {
      int left = l - 1;
      while (left > 0 && ((eq[left - 1] >= '0' && eq[left - 1] <= '9') ||
                          eq[left - 1] == '.')) {
        left--;
      }
      int right = l + 1;
      while (eq[right + 1] != '\0' &&
             (eq[right + 1] >= '0' && eq[right + 1] <= '9')) {
        right++;
      }
      float number = atof(&eq[left]);
      int power_val = atof(&eq[l + 1]);
      ans = power(number, (int)power_val);
      sprintf(tempResult, "%g", ans);

      int ansLen = strlen(tempResult);
      int maxShift = right + 1;
      int charsToMove = strlen(eq) - maxShift + 1;

      memmove(&eq[left + ansLen], &eq[maxShift], charsToMove);
      memcpy(&eq[left], tempResult, ansLen);
      l = 0;
    } else {
      l++;
    }
  }

  while (i < strlen(eq)) {
    char tempResult[32];
    if (eq[i] == '*' || eq[i] == '/') {
      int left = i - 1;
      while (left > 0 && ((eq[left - 1] >= '0' && eq[left - 1] <= '9') ||
                          eq[left - 1] == '.')) {
        left--;
      }
      int right = i + 1;
      while (eq[right + 1] != '\0' &&
             ((eq[right + 1] >= '0' && eq[right + 1] <= '9') ||
              eq[right + 1] == '.')) {
        right++;
      }
      float num1 = atof(&eq[left]);
      float num2 = atof(&eq[i + 1]);
      char operator = eq[i];
      if (operator == '*') {
        ans = mul(num1, num2);
      } else if (operator == '/') {
        ans = divide(num1, num2);
      }

      sprintf(tempResult, "%g", ans);

      int ansLen = strlen(tempResult);
      int maxShift = right + 1;
      int charsToMove = strlen(eq) - maxShift + 1;

      memmove(&eq[left + ansLen], &eq[maxShift], charsToMove);
      memcpy(&eq[left], tempResult, ansLen);

      i = 0;
    } else {
      i++;
    }
  }
  while (j < strlen(eq)) {
    char tempResult[32];
    if (eq[j] == '+' || eq[j] == '-') {
      int left = j - 1;
      while (left > 0 && ((eq[left - 1] >= '0' && eq[left - 1] <= '9') ||
                          eq[left - 1] == '.')) {
        left--;
      }

      int right = j + 1;
      while (eq[right + 1] != '\0' &&
             ((eq[right + 1] >= '0' && eq[right + 1] <= '9') ||
              eq[right + 1] == '.')) {
        right++;
      }

      float num1 = atof(&eq[left]);
      float num2 = atof(&eq[j + 1]);
      char operator = eq[j];
      if (operator == '+') {
        ans = add(num1, num2);
      } else if (operator == '-') {
        ans = sub(num1, num2);
      }

      sprintf(tempResult, "%g", ans);

      int ansLen = strlen(tempResult);

      int maxShift = right + 1;
      int charsToMove = strlen(eq) - maxShift + 1;

      memmove(&eq[left + ansLen], &eq[maxShift], charsToMove);
      memcpy(&eq[left], tempResult, ansLen);

      j = 0;
    } else {
      j++;
    }
  }
  return eq;
}
