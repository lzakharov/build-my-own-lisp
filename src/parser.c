#include "parser.h"
#include "mpc.h"

void parser_init() {
  mpc_parser_t* number = mpc_new("number");
  mpc_parser_t* operator = mpc_new("operator");
  mpc_parser_t* expr = mpc_new("expr");
  mpc_parser_t* lispy = mpc_new("lispy");

  mpca_lang(MPCA_LANG_DEFAULT, LANG, number, operator, expr, lispy);
  parser_number = number;
  parser_operator = operator;
  parser_expr = expr;
  parser_lispy = lispy;
}

int parser_parse(const char* filename, const char* string, mpc_result_t* r) {
  return mpc_parse(filename, string, parser_lispy, r);
}

void parser_cleanup() {
  mpc_cleanup(4, parser_number, parser_operator, parser_expr, parser_lispy);
}
