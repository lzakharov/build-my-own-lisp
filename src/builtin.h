#ifndef BUILTIN_H
#define BUILTIN_H

#include "lval.h"
#include "lenv.h"

#define LASSERT(args, cond, err) \
  if (!(cond)) { lval_del((args)); return lval_err((err)); }

lval* builtin_op(const lenv* e, lval* a, const char* op);
lval* builtin_add(lenv* e, lval* a);
lval* builtin_sub(lenv* e, lval* a);
lval* builtin_mul(lenv* e, lval* a);
lval* builtin_div(lenv* e, lval* a);

lval* builtin_list(lenv* e, lval* a);
lval* builtin_head(lenv* e, lval* a);
lval* builtin_tail(lenv* e, lval* a);
lval* builtin_join(lenv* e, lval* a);
lval* builtin_eval(lenv* e, lval* a);

lval* builtin_def(lenv* e, lval* a);

#endif
