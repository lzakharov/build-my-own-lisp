#include "parser.h"

#include "mpc.h"

parser_grammar* parser_init(void) {
  parser_grammar* g = malloc(sizeof(parser_grammar));
  g->number = mpc_new("number");
  g->symbol = mpc_new("symbol");
  g->sexpr = mpc_new("sexpr");
  g->qexpr = mpc_new("qexpr");
  g->expr = mpc_new("expr");
  g->lispy = mpc_new("lispy");
  mpca_lang(MPCA_LANG_DEFAULT, LANG, g->number, g->symbol,
	    g->sexpr, g->qexpr, g->expr, g->lispy);
  return g;
}

int parser_parse(const char* filename, const char* string, const parser_grammar* g,
		 mpc_result_t* r) {
  return mpc_parse(filename, string, g->lispy, r);
}

void parser_cleanup(parser_grammar* g) {
  mpc_cleanup(6, g->number, g->symbol, g->sexpr, g->qexpr, g->expr, g->lispy);
  free(g);
}
