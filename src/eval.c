#include "eval.h"

#include <stdio.h>

#include "mpc.h"
#include "parser.h"
#include "lval.h"

void eval_print(const parser_grammar* g, const char* input) {
  mpc_result_t r;
  if (parser_parse("<stdin>", input, g, &r)) {
    lval result = eval(r.output);
    lval_print(result);
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

lval eval_op(const lval x, const char* op, const lval y) {
  if (x.type == LVAL_ERR) { return x; };
  if (y.type == LVAL_ERR) { return x; };

  if (strcmp(op, "+") == 0) { return lval_num(x.num + y.num); };
  if (strcmp(op, "-") == 0) { return lval_num(x.num - y.num); };
  if (strcmp(op, "*") == 0) { return lval_num(x.num * y.num); };
  if (strcmp(op, "/") == 0) {
    return y.num == 0 ? lval_err(LERR_DIV_ZERO) : lval_num(x.num / y.num);
  };

  return lval_err(LERR_BAD_OP);
}

lval eval(const mpc_ast_t* t) {
  if (strstr(t->tag, "number")) {
    errno = 0;
    long x = strtol(t->contents, NULL, 10);
    return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_NUM);
  }

  char* op = t->children[1]->contents;
  lval x = eval(t->children[2]);

  int i = 3;
  while (strstr(t->children[i]->tag, "expr")) {
    x = eval_op(x, op, eval(t->children[i]));
    ++i;
  }

  return x;
}
