#ifndef BUILTIN_H
#define BUILTIN_H

#include "lval.h"
#include "lenv.h"

#define LASSERT(args, cond, err) \
  if (!(cond)) { lval_del((args)); return lval_err((err)); }

lval* builtin_op(const lenv* e, lval* a, const char* op);
lval* builtin_add(const lenv* e, lval* a);
lval* builtin_sub(const lenv* e, lval* a);
lval* builtin_mul(const lenv* e, lval* a);
lval* builtin_div(const lenv* e, lval* a);
lval* builtin_list(const lenv* e, lval* a);
lval* builtin_head(const lenv* e, lval* a);
lval* builtin_tail(const lenv* e, lval* a);
lval* builtin_join(const lenv* e, lval* a);
lval* builtin_eval(const lenv* e, lval* a);

#endif
