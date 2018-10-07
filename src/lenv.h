#ifndef LENV_H
#define LENV_H

#include "lval.h"

struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;

typedef lval*(*lbuiltin)(lenv*, lval*);

struct lenv {
  lenv* par;
  int count;
  char** syms;
  lval** vals;
};

lenv* lenv_new(void);
void lenv_del(lenv* e);
lenv* lenv_copy(lenv* e);

lval* lenv_get(const lenv* e, const lval* k);
void lenv_put(lenv* e, const lval* k, const lval* v);
void lenv_def(lenv* e, const lval* k, const lval* v);

void lenv_add_builtin(lenv* e, const char* name, const lbuiltin func);
void lenv_add_builtins(lenv* e);
void lenv_load_file(lenv* e, const char* filename);

#endif
