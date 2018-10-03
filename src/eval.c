#include "eval.h"

#include <stdio.h>

#include "mpc.h"
#include "parser.h"

void eval_print(const parser_grammar* g, const char* input) {
  mpc_result_t r;
  if (parser_parse("<stdin>", input, g, &r)) {
    long result = eval(r.output);
    printf("%li", result);
    mpc_ast_delete(r.output);
  } else {
    mpc_err_print(r.error);
    mpc_err_delete(r.error);
  }
}

void eval_println(const parser_grammar* g, const char* input) {
  eval_print(g, input);
  putchar('\n');
}

long eval_op(const long x, const char* op, const long y) {
  if (strcmp(op, "+") == 0) { return x + y; };
  if (strcmp(op, "-") == 0) { return x - y; };
  if (strcmp(op, "*") == 0) { return x * y; };
  if (strcmp(op, "/") == 0) { return x / y; };
  return 0;
}

long eval(const mpc_ast_t* t) {
  if (strstr(t->tag, "number")) {
    return atoi(t->contents);
  }

  char* op = t->children[1]->contents;
  long x = eval(t->children[2]);

  int i = 3;
  while (strstr(t->children[i]->tag, "expr")) {
    x = eval_op(x, op, eval(t->children[i]));
    ++i;
  }

  return x;
}
