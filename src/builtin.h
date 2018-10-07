#ifndef BUILTIN_H
#define BUILTIN_H

#include "lval.h"
#include "ltype.h"
#include "lenv.h"

#define LASSERT(args, cond, fmt, ...) \
  if (!(cond)) { lval* err = lval_err(fmt, ##__VA_ARGS__); lval_del(args); return err; }

#define LASSERT_TYPE(func, args, index, expect) \
  LASSERT(args, args->cell[index]->type == expect, \
    "Function '%s' passed incorrect type for argument %i. " \
    "Got %s, Expected %s.", \
    func, index, ltype_name(args->cell[index]->type), ltype_name(expect))

#define LASSERT_NUM(func, args, num) \
  LASSERT(args, args->count == num, \
    "Function '%s' passed incorrect number of arguments. " \
    "Got %i, Expected %i.", \
    func, args->count, num)

#define LASSERT_NOT_EMPTY(func, args, index) \
  LASSERT(args, args->cell[index]->count != 0, \
    "Function '%s' passed {} for argument %i.", func, index);

/* Math Functions */
lval* builtin_op(const lenv* e, lval* a, const char* op);
lval* builtin_add(lenv* e, lval* a);
lval* builtin_sub(lenv* e, lval* a);
lval* builtin_mul(lenv* e, lval* a);
lval* builtin_div(lenv* e, lval* a);

/* Comparison Functions */
lval* builtin_ord(const lenv* e, lval* a, const char* op);
lval* builtin_gt(lenv* e, lval* a);
lval* builtin_ge(lenv* e, lval* a);
lval* builtin_lt(lenv* e, lval* a);
lval* builtin_le(lenv* e, lval* a);
lval* builtin_cmp(const lenv* e, lval* a, const char* op);
lval* builtin_eq(lenv* e, lval* a);
lval* builtin_ne(lenv* e, lval* a);

/* Logical Functions */
lval* builtin_if(lenv* e, lval* a);
lval* builtin_or(lenv* e, lval* a);
lval* builtin_and(lenv* e, lval* a);
lval* builtin_not(lenv* e, lval* a);

/* List Functions */
lval* builtin_list(lenv* e, lval* a);
lval* builtin_head(lenv* e, lval* a);
lval* builtin_tail(lenv* e, lval* a);
lval* builtin_join(lenv* e, lval* a);
lval* builtin_eval(lenv* e, lval* a);

/* Variable Functions */
lval* builtin_def(lenv* e, lval* a);
lval* builtin_put(lenv* e, lval* a);
lval* builtin_fun(lenv* e, lval* a);
lval* builtin_var(lenv* e, lval* a, const char* func);
lval* builtin_lambda(lenv* e, lval* a);
lval* builtin_locals(lenv* e, lval* a);

lval* builtin_load(lenv* e, lval* a);
lval* builtin_print(lenv* e, lval* a);
lval* builtin_error(lenv* e, lval* a);

lval* builtin_exit(lenv* e, lval* a);

#endif
