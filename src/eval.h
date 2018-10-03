#ifndef EVAL_H
#define EVAL_H

#include "mpc.h"
#include "parser.h"

void eval_print(const parser_grammar* g, const char* input);
void eval_println(const parser_grammar* g, const char* input);
long eval(const mpc_ast_t* t);
long eval_op(const long x, const char* op, const long y);

#endif
