#include "lval.h"

#include <stdio.h>

lval lval_num(const long num) {
  lval v;
  v.type = LVAL_NUM;
  v.num = num;
  return v;
}

lval lval_err(const lerr_t err) {
  lval v;
  v.type = LVAL_ERR;
  v.err = err;
  return v;
}

void lval_print(const lval v) {
  switch (v.type) {
  case LVAL_NUM: printf("%li", v.num); break;
  case LVAL_ERR:
    if (v.err == LERR_DIV_ZERO) {
      printf("Error: Division By Zero!");
    }
    if (v.err == LERR_BAD_OP)   {
      printf("Error: Invalid Operator!");
    }
    if (v.err == LERR_BAD_NUM)  {
      printf("Error: Invalid Number!");
    }
    break;
  }
}

void lval_println(const lval v) {
  lval_print(v);
  putchar('\n');
}
