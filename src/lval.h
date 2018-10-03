#ifndef LVAL_H
#define LVAL_H

#include "mpc.h"

typedef enum { LVAL_NUM, LVAL_SYM, LVAL_SEXPR, LVAL_QEXPR, LVAL_ERR } lval_t;

typedef struct lval {
  lval_t type;
  long num;
  char* sym;
  char* err;
  
  int count;
  struct lval** cell;
} lval;

lval* lval_num(const long x);
lval* lval_sym(const char* s);
lval* lval_sexpr(void);
lval* lval_qexpr(void);
lval* lval_err(const char* m);

void lval_del(lval* v);

lval* lval_read_num(const mpc_ast_t* t);
lval* lval_read(const mpc_ast_t* t);

lval* lval_add(lval* v, const lval* x);
lval* lval_join(lval* x, lval* y);

lval* lval_eval_sexpr(lval* v);
lval* lval_eval(lval* v);
lval* lval_pop(lval* v, const int i);
lval* lval_take(lval* v, const int i);

void lval_expr_print(const lval* v, const char open, const char close);
void lval_print(const lval* v);
void lval_println(const lval* v);

#endif
