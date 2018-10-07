#include "lenv.h"

#include "lval.h"
#include "builtin.h"

lenv* lenv_new(void) {
  lenv* e = malloc(sizeof(lenv));
  e->par = NULL;
  e->count = 0;
  e->syms = NULL;
  e->vals = NULL;
  return e;
}

void lenv_del(lenv* e) {
  for (int i = 0; i < e->count; ++i) {
    free(e->syms[i]);
    lval_del(e->vals[i]);
  }
  free(e->syms);
  free(e->vals);
  free(e);
}

lenv* lenv_copy(lenv* e) {
  lenv* n = malloc(sizeof(lenv));
  n->par = e->par;
  n->count = e->count;
  n->syms = malloc(sizeof(char*) * n->count);
  n->vals = malloc(sizeof(lval*) * n->count);

  for (int i = 0; i < e->count; ++i) {
    n->syms[i] = malloc(strlen(e->syms[i]) + 1);
    strcpy(n->syms[i], e->syms[i]);
    n->vals[i] = lval_copy(e->vals[i]);
  }

  return n;
}

lval* lenv_get(const lenv* e, const lval* k) {
  for (int i = 0; i < e->count; ++i) {
    if (strcmp(e->syms[i], k->sym) == 0) {
      return lval_copy(e->vals[i]);
    }
  }

  if (e->par) {
    return lenv_get(e->par, k);
  }
  return lval_err("Unbound Symbol '%s'", k->sym);
}

void lenv_put(lenv* e, const lval* k, const lval* v) {
  for (int i = 0; i < e->count; ++i) {
    if (strcmp(e->syms[i], k->sym) == 0) {
      lval_del(e->vals[i]);
      e->vals[i] = lval_copy(v);
      return;
    }
  }

  e->count++;
  e->vals = realloc(e->vals, sizeof(lval*) * e->count);
  e->syms = realloc(e->syms, sizeof(char*) * e->count);
  e->vals[e->count-1] = lval_copy(v);
  e->syms[e->count-1] = malloc(strlen(k->sym) + 1);
  strcpy(e->syms[e->count-1], k->sym);
}

void lenv_def(lenv* e, const lval* k, const lval* v) {
  while (e->par) {
    e = e->par;
  }
  lenv_put(e, k, v);
}

void lenv_add_builtin(lenv* e, const char* name, const lbuiltin func) {
  lval* k = lval_sym(name);
  lval* v = lval_builtin(func);
  lenv_put(e, k, v);
  lval_del(k);
  lval_del(v);
}

void lenv_add_builtins(lenv* e) {
  /* Math Functions */
  lenv_add_builtin(e, "+", builtin_add);
  lenv_add_builtin(e, "-", builtin_sub);
  lenv_add_builtin(e, "*", builtin_mul);
  lenv_add_builtin(e, "/", builtin_div);

  /* Comparison Functions */
  lenv_add_builtin(e, ">", builtin_gt);
  lenv_add_builtin(e, ">=", builtin_ge);
  lenv_add_builtin(e, "<", builtin_lt);
  lenv_add_builtin(e, "<=", builtin_le);
  lenv_add_builtin(e, "==", builtin_eq);
  lenv_add_builtin(e, "!=", builtin_ne);

  /* Logical Functions */
  lenv_add_builtin(e, "if", builtin_if);
  lenv_add_builtin(e, "or", builtin_or);
  lenv_add_builtin(e, "and", builtin_and);
  lenv_add_builtin(e, "not", builtin_not);

  /* List Functions */
  lenv_add_builtin(e, "list", builtin_list);
  lenv_add_builtin(e, "head", builtin_head);
  lenv_add_builtin(e, "tail", builtin_tail);
  lenv_add_builtin(e, "eval", builtin_eval);
  lenv_add_builtin(e, "join", builtin_join);

  /* Function Functions */
  lenv_add_builtin(e, "def", builtin_def);
  lenv_add_builtin(e, "\\", builtin_lambda);
  lenv_add_builtin(e, "fun", builtin_fun);
  lenv_add_builtin(e, "=",   builtin_put);
  lenv_add_builtin(e, "locals", builtin_locals);

  lenv_add_builtin(e, "load", builtin_load);
  lenv_add_builtin(e, "print", builtin_print);
  lenv_add_builtin(e, "error", builtin_error);

  /* System Functions */
  lenv_add_builtin(e, "exit", builtin_exit);
}

void lenv_load_file(lenv* e, const char* filename) {
  printf("Loading '%s'\n", filename);
  lval* args = lval_add(lval_sexpr(), lval_str(filename));
  lval* x = builtin_load(e, args);
  if (x->type == LVAL_ERR) {
    lval_println(x);
  }
}
