#include <stdlib.h>

#include "parser.h"
#include "lenv.h"
#include "builtin.h"
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

void info(void);
void read_eval_print(const parser_grammar* g, lenv* e, const char* input);

int main(int argc, char** argv) {
  parser_grammar* g = parser_init();
  lenv* e = lenv_new();
  lenv_add_builtins(e);

  info();

  while (1) {
    char* input = readline("lispy> ");
    add_history(input);
    read_eval_print(g, e, input);
    free(input);
  }

  lenv_del(e);
  parser_cleanup(g);

  return 0;
}

void info(void) {
  puts("Lispy Version 0.0.0.0.6");
  puts("Press Ctrl+C to Exit\n");
}

void read_eval_print(const parser_grammar* g, lenv* e, const char* input) {
  mpc_result_t r;

  if (parser_parse("<stdin>", input, g, &r)) {
    lval* x = lval_eval(e, lval_read(r.output)); 
    lval_println(x);
    lval_del(x);
    mpc_ast_delete(r.output);
  } else {
    mpc_err_print(r.error);
    mpc_err_delete(r.error);
  }
}
