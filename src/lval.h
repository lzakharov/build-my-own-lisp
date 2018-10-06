#ifndef LVAL_H
#define LVAL_H

#include "mpc.h"
#include "lenv.h"

struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;

typedef enum { LVAL_NUM, LVAL_SYM, LVAL_STR, LVAL_FUN,
               LVAL_SEXPR, LVAL_QEXPR, LVAL_ERR } lval_t;

typedef lval*(*lbuiltin)(lenv*, lval*);

struct lval {
  lval_t type;

  /* Basics */
  long num;
  char* sym;
  char* err;
  char* str;
  
  /* Function */
  lbuiltin builtin;
  lenv* env;
  lval* formals;
  lval* body;

  /* Expression */
  int count;
  struct lval** cell;
};

lval* lval_num(const long x);
lval* lval_sym(const char* s);
lval* lval_err(char* fmt, ...);
lval* lval_str(const char* s);
lval* lval_builtin(const lbuiltin func);
lval* lval_lambda(lval* formals, lval* body);
lval* lval_sexpr(void);
lval* lval_qexpr(void);

void lval_del(lval* v);

lval* lval_read_num(const mpc_ast_t* t);
lval* lval_read_str(const mpc_ast_t* t);
lval* lval_read(const mpc_ast_t* t);

int lval_eq(const lval* x, const lval* y);

lval* lval_add(lval* v, const lval* x);
lval* lval_join(lval* x, lval* y);
lval* lval_copy(const lval* v);

lval* lval_call(lenv* e, lval* f, lval* a);
lval* lval_eval_sexpr(lenv* e, lval* v);
lval* lval_eval(lenv* e, lval* v);
lval* lval_pop(lval* v, const int i);
lval* lval_take(lval* v, const int i);

void lval_print_str(const lval* v);
void lval_print_expr(const lval* v, const char open, const char close);
void lval_print(const lval* v);
void lval_println(const lval* v);

#endif
