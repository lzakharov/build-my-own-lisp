#include "builtin.h"

#include "lval.h"
#include "lenv.h"

lval* builtin_op(const lenv* e, lval* a, const char* op) {
  for (int i = 0; i < a->count; ++i) {
    if (a->cell[i]->type != LVAL_NUM) {
      lval_del(a);
      return lval_err("Cannot operate on non-number!");
    }
  }

  lval* x = lval_pop(a, 0);

  if (strcmp(op, "-") == 0 && a->count == 0) { x->num = -x->num; }

  while (a->count) {
    lval* y = lval_pop(a, 0);

    if (strcmp(op, "+") == 0) { x->num += y->num; }
    if (strcmp(op, "-") == 0) { x->num -= y->num; }
    if (strcmp(op, "*") == 0) { x->num *= y->num; }
    if (strcmp(op, "/") == 0) {
      if (y->num == 0) {
        lval_del(x);
        lval_del(y);
        x = lval_err("Division By Zero!");
        break;
      }
      x->num /= y->num;
    };

    lval_del(y);
  }

  lval_del(a);
  return x;
}

lval* builtin_add(const lenv* e, lval* a) {
  return builtin_op(e, a, "+");
}

lval* builtin_sub(const lenv* e, lval* a) {
  return builtin_op(e, a, "-");
}

lval* builtin_mul(const lenv* e, lval* a) {
  return builtin_op(e, a, "*");
}

lval* builtin_div(const lenv* e, lval* a) {
  return builtin_op(e, a, "/");
}

lval* builtin_list(const lenv* e, lval* a) {
  a->type = LVAL_QEXPR;
  return a;
}

lval* builtin_head(const lenv* e, lval* a) {
  LASSERT(a, a->count == 1,
	  "Function 'head' passed too many arguments!");
  LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
	  "Function 'head' passed incorrect types!");
  LASSERT(a, a->cell[0]->count != 0,
	  "Function 'head' passed {}!");

  lval* v = lval_take(a, 0);
  while (v->count > 1) {
    lval_del(lval_pop(v, 1));
  }

  return v;
}

lval* builtin_tail(const lenv* e, lval* a) {
  LASSERT(a, a->count == 1,
	  "Function 'tail' passed too many arguments!");
  LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
	  "Function 'tail' passed incorrect types!");
  LASSERT(a, a->cell[0]->count != 0,
	  "Function 'tail' passed {}!");

  lval* v = lval_take(a, 0);
  lval_del(lval_pop(v, 0));

  return v;
}

lval* builtin_eval(const lenv* e, lval* a) {
  LASSERT(a, a->count == 1,
	  "Function 'eval' passed too many arguments!");
  LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
	  "Function 'eval' passed incorrect types!");

  lval* x = lval_pop(a, 0);
  x->type = LVAL_SEXPR;
  return lval_eval(e, x);
}

lval* builtin_join(const lenv* e, lval* a) {
  for (int i = 0; i < a->count; ++i) {
    LASSERT(a, a->cell[i]->type == LVAL_QEXPR,
	    "Function 'join' passed incorrect type.");
  }

  lval* x = lval_pop(a, 0);
  while (a->count) {
    x = lval_join(x, lval_pop(a, 0));
  }

  lval_del(a);
  return x;
}
