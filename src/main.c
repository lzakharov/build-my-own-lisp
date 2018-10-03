#include <stdlib.h>

#include "parser.h"
#include "eval.h"

#ifdef _WIN32
#include <string.h>

static char buffer[2048];

char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

void add_history(char* input) {}
#elif __APPLE__
#include <editline/readline.h>
#elif __linux
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char** argv) {
  parser_grammar* g = parser_init();

  puts("Lispy Version 0.0.0.0.4");
  puts("Press Ctrl+C to Exit\n");

  while (1) {
    char* input = readline("lispy> ");
    add_history(input);
    eval_println(g, input);
    free(input);
  }

  parser_cleanup();
  return 0;
}
