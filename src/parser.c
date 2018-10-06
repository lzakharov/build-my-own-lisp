#include "parser.h"

#include "mpc.h"

void parser_init(void) {
  g = malloc(sizeof(parser_grammar));
  g->number = mpc_new("number");
  g->symbol = mpc_new("symbol");
  g->string = mpc_new("string");
  g->comment = mpc_new("comment");
  g->sexpr = mpc_new("sexpr");
  g->qexpr = mpc_new("qexpr");
  g->expr = mpc_new("expr");
  g->lispy = mpc_new("lispy");
  mpca_lang(MPCA_LANG_DEFAULT, LANG, g->number, g->symbol, g->string,
            g->comment, g->sexpr, g->qexpr, g->expr, g->lispy);
}

int parser_parse(const char* filename, const char* string,
                 mpc_result_t* r) {
  return mpc_parse(filename, string, g->lispy, r);
}

int parser_parse_contents(const char* filename, mpc_result_t* r) {
  return mpc_parse_contents(filename, g->lispy, r);
}

void parser_cleanup(void) {
  mpc_cleanup(8, g->number, g->symbol, g->string, g->comment,
              g->sexpr, g->qexpr, g->expr, g->lispy);
  free(g);
}
