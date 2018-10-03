#include <stdlib.h>

#include "parser.h"
#include "lval.h"

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

void read_eval_print(const parser_grammar* g, const char* input);

int main(int argc, char** argv) {
  parser_grammar* g = parser_init();

  puts("Lispy Version 0.0.0.0.5");
  puts("Press Ctrl+C to Exit\n");

  while (1) {
    char* input = readline("lispy> ");
    add_history(input);

    read_eval_print(g, input);

    free(input);
  }

  parser_cleanup(g);
  return 0;
}

void read_eval_print(const parser_grammar* g, const char* input) {
  mpc_result_t r;

  if (parser_parse("<stdin>", input, g, &r)) {
    lval* x = lval_eval(lval_read(r.output)); 
    lval_println(x);
    lval_del(x);
    mpc_ast_delete(r.output);
  } else {
    mpc_err_print(r.error);
    mpc_err_delete(r.error);
  }
}
