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
float absolute(float num) {
  if (num < 0) {
    return -num;
  }
  return num;
}
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
float power(float base, int pwr) {
  int absPower = absolute((float)pwr);
  if (absPower == 0) {
    return 1;
  }
  int i = 1;
  float product = base;
  while (i < absPower) {
    product = product * base;
    i++;
  }
  print_working(base, (float)absPower, product, 5);
  if (pwr < 0) {
    product = divide(1, product);
  }
  print_working(base, (float)pwr, product, 5);
  return product;
}
char *bodmas(char *input_equation) {
  /*
  Handles bodmas with functionality for all cases that being
  B - Brackets
  O - Orders (Powers)
  D - Division
  M - Multiplaction
  A - Addition
  S - Subtraction

  Inputs:
   - *input_equation - the original equation given by the user
  Outputs:
   - eq: The answer to the equation
  */

  // Create a clone of the input equation to modify and answer
  char *eq = strdup(input_equation);
  if (eq == NULL) {
    return NULL;
  }

  float ans;
  int i = 0;
  int j = 0;
  int l = 0;
  // Search for B(brackets) to fulfil bodmas requirements
  while (strchr(eq, '(')) {
    // Now calculate the amount of chars situated within the bracket
    int start = 0, end = 0;
    for (int k = 0; k < strlen(eq); k++) {
      if (eq[k] == '(')
        start = k;
      if (eq[k] == ')') {
        end = k;
        break;
      }
    }
    // the range subtracts 1 to exclude the starter parenthesis
    int insideBracketRange = end - start - 1;
    // Make a new array for the equation within the bracket
    //+1 to include null terminator for strncpy
    char *interBracketEq = malloc(insideBracketRange + 1);
    strncpy(interBracketEq, &eq[start + 1], insideBracketRange);
    interBracketEq[insideBracketRange] = '\0';
    // Recurse the equation within the bracket to do bodmas within the bracket
    // as well
    char *interAns = bodmas(interBracketEq);

    if (interAns) {
      int ansLen = strlen(interAns);
      // Calculate remaining string including null terminator
      int remainingLen = strlen(&eq[end + 1]) + 1;
      // Make room or shrink space for the new answer
      memmove(&eq[start + ansLen], &eq[end + 1], remainingLen);
      memcpy(&eq[start], interAns, ansLen);

      free(interAns);
    }

    free(interBracketEq);
  }
  // Handle orders(currently only powers)
  while (l < strlen(eq)) {
    char tempResult[64];
    if (eq[l] == '^') {
      // Find the entire number on the left side including signs
      int left = l - 1;
      while (left > 0 && ((eq[left - 1] >= '0' && eq[left - 1] <= '9') ||
                          eq[left - 1] == '.')) {
        left--;
      }
      if (left > 0 && eq[left - 1] == '-') {
        left--;
      }

      // Find the entire number to the right including signs
      int right = l + 1;
      if (eq[right] == '-') {
        right++;
      }
      while (eq[right + 1] != '\0' &&
             ((eq[right + 1] >= '0' && eq[right + 1] <= '9') ||
              eq[right + 1] == '.')) {
        right++;
      }

      // Convert strings into floats and get answer
      float number = atof(&eq[left]);
      float powerVal = atof(&eq[l + 1]);
      ans = power(number, (int)powerVal);

      // Convert answer to string
      sprintf(tempResult, "%g", ans);
      // Get amount of characters in answer
      int ansLen = strlen(tempResult);
      // We only care about the values to the right since that is the only
      // values we cut and pull The left can just be replaced by the answer
      int maxShift = right + 1;
      int charsToMove = strlen(eq) - maxShift + 1;
      // Cut and move the right side of the equation
      memmove(&eq[left + ansLen], &eq[maxShift], charsToMove);
      memcpy(&eq[left], tempResult, ansLen);
      // Reset l to check the entire equation for another power
      l = 0;
    } else {
      l++;
    }
  }
  while (i < strlen(eq)) {
    // Same logic as orders but multiplaction and division
    char tempResult[64];
    if (eq[i] == '*' || eq[i] == '/') {
      int left = i - 1;
      while (left > 0 && ((eq[left - 1] >= '0' && eq[left - 1] <= '9') ||
                          eq[left - 1] == '.')) {
        left--;
      }
      if (left > 0 && eq[left - 1] == '-') {
        left--;
      }

      int right = i + 1;
      if (eq[right] == '-') {
        right++;
      }
      while (eq[right + 1] != '\0' &&
             ((eq[right + 1] >= '0' && eq[right + 1] <= '9') ||
              eq[right + 1] == '.')) {
        right++;
      }

      float num1 = atof(&eq[left]);
      float num2 = atof(&eq[i + 1]);
      char operator = eq[i];

      if (operator == '*')
        ans = mul(num1, num2);
      else if (operator == '/')
        ans = divide(num1, num2);

      sprintf(tempResult, "%g", ans);
      int ansLen = strlen(tempResult);
      int maxShift = right + 1;
      int charsToMove = strlen(eq) - maxShift + 1;

      if (charsToMove > 0) {
        memmove(&eq[left + ansLen], &eq[maxShift], charsToMove);
      } else {
        eq[left + ansLen] = '\0';
      }
      memcpy(&eq[left], tempResult, ansLen);
      i = 0;
    } else {
      i++;
    }
  }
  while (j < strlen(eq)) {
    // Same logic multiplaction and division just with additiion and subtraction
    char tempResult[64];
    if ((eq[j] == '+' || eq[j] == '-') && j > 0) {
      int left = j - 1;
      while (left > 0 && ((eq[left - 1] >= '0' && eq[left - 1] <= '9') ||
                          eq[left - 1] == '.')) {
        left--;
      }
      if (left > 0 && eq[left - 1] == '-') {
        left--;
      }

      int right = j + 1;
      if (eq[right] == '-') {
        right++;
      }
      while (eq[right + 1] != '\0' &&
             ((eq[right + 1] >= '0' && eq[right + 1] <= '9') ||
              eq[right + 1] == '.')) {
        right++;
      }

      float num1 = atof(&eq[left]);
      float num2 = atof(&eq[j + 1]);
      char operator = eq[j];

      if (operator == '+')
        ans = add(num1, num2);
      else if (operator == '-')
        ans = sub(num1, num2);

      sprintf(tempResult, "%g", ans);
      int ansLen = strlen(tempResult);
      int maxShift = right + 1;
      int charsToMove = strlen(eq) - maxShift + 1;

      if (charsToMove > 0) {
        memmove(&eq[left + ansLen], &eq[maxShift], charsToMove);
      } else {
        eq[left + ansLen] = '\0';
      }
      memcpy(&eq[left], tempResult, ansLen);
      j = 0;
    } else {
      j++;
    }
  }
  return eq;
}
