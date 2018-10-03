#ifndef PARSER_H
#define PARSER_H

#include "mpc.h"

static const char* LANG =
  "number   : /-?[0-9]+/ ;"
  "operator : '+' | '-' | '*' | '/' ;"
  "expr     : <number> | '(' <operator> <expr>+ ')' ;"
  "lispy    : /^/ <operator> <expr>+ /$/ ;";

typedef struct {
    mpc_parser_t* number;
    mpc_parser_t* operator;
    mpc_parser_t* expr;
    mpc_parser_t* lispy;
} parser_grammar;

parser_grammar* parser_init();
int parser_parse(const char* filename, const char* string, const parser_grammar* g,
		 mpc_result_t* r);
void parser_cleanup();

#endif
