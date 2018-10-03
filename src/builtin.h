#ifndef BUILTIN_H
#define BUILTIN_H

#include "lval.h"

#define LASSERT(args, cond, err) \
  if (!(cond)) { lval_del((args)); return lval_err((err)); }

lval* builtin(lval* a, const char* func);
lval* builtin_op(lval* a, const char* op);
lval* builtin_list(lval* a);
lval* builtin_head(lval* a);
lval* builtin_tail(lval* a);
lval* builtin_join(lval* a);
lval* builtin_eval(lval* a);

#endif
