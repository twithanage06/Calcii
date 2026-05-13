/*
 AUTHOR/S: THANUJA A.W
 DATE: 12/05/2026
 VERSION: 0.1.0
 */
#include "matfunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

void help() {
  char *commands[] = {"\x1b[1mGENERAL FUNCTIONALITY\x1b[0m --",
                      "\x1b[1mh\x1b[0m - Generate a list of commands possible",
                      "\x1b[1mq\x1b[0m - Quit the program\n",
                      "\x1b[1mEQUATION FLAGS\x1b[0m --",
                      "\x1b[1mFor all [Equation] please format it with no "
                      "spaces\x1b[0m\n-- \x1b[1mE.g: "
                      "(3+2)-4*5/(6^2)\x1b[0m\n",
                      "\x1b[1ma [Equation] \x1b[0m- Do arithmetic(BODMAS) "
                      "calculations with the "
                      "equation inputted"};
  int num_commands = sizeof(commands) / sizeof(commands[0]);

  for (int i = 0; i < num_commands; i++) {
    printf("-- %s\n", commands[i]);
  }
}
int main() {
  char flag;
  char *eq = malloc(1024 * sizeof(char));

  if (eq == NULL) {
    return -1;
  }
  printf("\n ██████╗ █████╗ ██╗      ██████╗██╗██╗\n"
         "██╔════╝██╔══██╗██║     ██╔════╝██║██║\n"
         "██║     ███████║██║     ██║     ██║██║\n"
         "██║     ██╔══██║██║     ██║     ██║██║\n"
         "╚██████╗██║  ██║███████╗╚██████╗██║██║\n"
         " ╚═════╝╚═╝  ╚═╝╚══════╝ ╚═════╝╚═╝╚═╝\n\n");
  printf("Welcome to Calcii your calculus calculator!\nType 'h' to see "
         "commands\n");
  while (1) {
    printf(GREEN "\n[calcii]> " RESET);
    scanf(" %c", &flag);
    switch (flag) {
    case 'h':
      help();
      break;
    case 'q':
      free(eq);
      return 0;
    case 'a':
      scanf("%s", eq);
      char *result_eq = bodmas(eq);
      printf("Original Equation: \x1b[1m%s\x1b[0m\n", eq);
      printf("Answer: \x1b[1m%s\x1b[0m", result_eq);
      free(result_eq);
      break;
    default:
      printf(RED "Not a valid command. Please type \x1b[1m'h'" RESET RED
                 " to get a "
                 "list of commands" RESET);
      int c;
      while ((c = getchar()) != '\n' && c != EOF)
        ;
      break;
    }
  }
  free(eq);

  return 0;
}
