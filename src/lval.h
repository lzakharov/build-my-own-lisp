#ifndef LVAL_H
#define LVAL_H

typedef enum { LVAL_NUM, LVAL_ERR } lval_t;
typedef enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM } lerr_t;

typedef struct {
  lval_t type;
  long num;
  lerr_t err;
} lval;

lval lval_num(const long num);
lval lval_err(const lerr_t err);
void lval_print(const lval v);
void lval_println(const lval v);

#endif
