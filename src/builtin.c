#include "builtin.h"

#include "lval.h"
#include "lenv.h"

lval* builtin_op(const lenv* e, lval* a, const char* op) {
  for (int i = 0; i < a->count; ++i) {
    if (a->cell[i]->type != LVAL_NUM) {
      LASSERT_TYPE(op, a, i, LVAL_NUM);
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

lval* builtin_add(lenv* e, lval* a) {
  return builtin_op(e, a, "+");
}

lval* builtin_sub(lenv* e, lval* a) {
  return builtin_op(e, a, "-");
}

lval* builtin_mul(lenv* e, lval* a) {
  return builtin_op(e, a, "*");
}

lval* builtin_div(lenv* e, lval* a) {
  return builtin_op(e, a, "/");
}

lval* builtin_list(lenv* e, lval* a) {
  a->type = LVAL_QEXPR;
  return a;
}

lval* builtin_head(lenv* e, lval* a) {
  LASSERT_NUM("head", a, 1);
  LASSERT_TYPE("head", a, 0, LVAL_QEXPR);
  LASSERT_NOT_EMPTY("head", a, 0);

  lval* v = lval_take(a, 0);
  while (v->count > 1) {
    lval_del(lval_pop(v, 1));
  }

  return v;
}

lval* builtin_tail(lenv* e, lval* a) {
  LASSERT_NUM("tail", a, 1);
  LASSERT_TYPE("tail", a, 0, LVAL_QEXPR);
  LASSERT_NOT_EMPTY("tail", a, 0);

  lval* v = lval_take(a, 0);
  lval_del(lval_pop(v, 0));

  return v;
}

lval* builtin_eval(lenv* e, lval* a) {
  LASSERT_NUM("eval", a, 1);
  LASSERT_TYPE("eval", a, 0, LVAL_QEXPR);

  lval* x = lval_pop(a, 0);
  x->type = LVAL_SEXPR;
  return lval_eval(e, x);
}

lval* builtin_join(lenv* e, lval* a) {
  for (int i = 0; i < a->count; ++i) {
    LASSERT_TYPE("join", a, i, LVAL_QEXPR);
  }

  lval* x = lval_pop(a, 0);
  while (a->count) {
    x = lval_join(x, lval_pop(a, 0));
  }

  lval_del(a);
  return x;
}

lval* builtin_def(lenv* e, lval* a) {
  LASSERT_TYPE("def", a, 0, LVAL_QEXPR);
  lval* syms = a->cell[0];

  for (int i = 0; i < syms->count; ++i) {
    LASSERT(a, (syms->cell[i]->type == LVAL_SYM),
            "Function 'def' cannot define non-symbol. "
            "Got %s, Expected %s.",
            ltype_name(syms->cell[i]->type), ltype_name(LVAL_SYM));
  }

  LASSERT(a, syms->count == a->count-1,
          "Function 'def' cannot define incorrect "
          "number of values to symbols");
 
  for (int i = 0; i < syms->count; ++i) {
    lenv_put(e, syms->cell[i], a->cell[i+1]);
  }

  lval_del(a);
  return lval_sexpr();
}
