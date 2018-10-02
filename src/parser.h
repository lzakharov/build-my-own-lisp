#ifndef PARSER_H
#define PARSER_H

#include "mpc.h"

static const char* LANG =
  "number   : /-?[0-9]+/ ;"
  "operator : '+' | '-' | '*' | '/' ;"
  "expr     : <number> | '(' <operator> <expr>+ ')' ;"
  "lispy    : /^/ <operator> <expr>+ /$/ ;";

static mpc_parser_t* parser_number = NULL;
static mpc_parser_t* parser_operator = NULL;
static mpc_parser_t* parser_expr = NULL;
static mpc_parser_t* parser_lispy = NULL;

void parser_init();
int parser_parse(const char* filename, const char* string, mpc_result_t* r);
void parser_cleanup();

#endif
