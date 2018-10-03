#include "parser.h"

#include "mpc.h"

parser_grammar* parser_init() {
  parser_grammar* g = malloc(sizeof(parser_grammar));
  g->number = mpc_new("number");
  g->operator = mpc_new("operator");
  g->expr = mpc_new("expr");
  g->lispy = mpc_new("lispy");
  mpca_lang(MPCA_LANG_DEFAULT, LANG, g->number, g->operator, g->expr, g->lispy);
  return g;
}

int parser_parse(const char* filename, const char* string, const parser_grammar* g,
		 mpc_result_t* r) {
  return mpc_parse(filename, string, g->lispy, r);
}

void parser_cleanup(parser_grammar* g) {
  mpc_cleanup(4, g->number, g->operator, g->expr, g->lispy);
  free(g);
}
