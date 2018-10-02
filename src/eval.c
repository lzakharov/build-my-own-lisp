#include "eval.h"
#include "mpc.h"
#include "parser.h"

void eval_print(const char* input) {
  mpc_result_t r;
  if (parser_parse("<stdin>", input, &r)) {
    long result = eval(r.output);
    printf("%li\n", result);
    mpc_ast_delete(r.output);
  } else {
    mpc_err_print(r.error);
    mpc_err_delete(r.error);
  }
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
