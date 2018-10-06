#ifndef PARSER_H
#define PARSER_H

#include "mpc.h"

static const char* LANG =
  "number   : /-?[0-9]+/ ;"
  "symbol   : /[a-zA-Z0-9_+\\-*\\/\\\\=<>!&]+/ ;"
  "string   : /\"(\\\\.|[^\"])*\"/ ;"
  "comment  : /;[^\\r\\n]*/ ;"
  "sexpr    : '(' <expr>* ')' ;"
  "qexpr    : '{' <expr>* '}' ;"
  "expr     : <number>  | <symbol> | <string> "
  "         | <comment> | <sexpr>  | <qexpr> ;"
  "lispy    : /^/ <expr>* /$/ ;";

typedef struct {
  mpc_parser_t* number;
  mpc_parser_t* symbol;
  mpc_parser_t* string;
  mpc_parser_t* comment;
  mpc_parser_t* sexpr;
  mpc_parser_t* qexpr;
  mpc_parser_t* expr;
  mpc_parser_t* lispy;
} parser_grammar;

static parser_grammar* g;

void parser_init(void);
int parser_parse(const char* filename, const char* string,
                 mpc_result_t* r);
int parser_parse_contents(const char* filename, mpc_result_t* r);
void parser_cleanup(void);

#endif
