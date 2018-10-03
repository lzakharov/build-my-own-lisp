#ifndef EVAL_H
#define EVAL_H

#include "mpc.h"
#include "parser.h"
#include "lval.h"

void eval_print(const parser_grammar* g, const char* input);
void eval_println(const parser_grammar* g, const char* input);
lval eval(const mpc_ast_t* t);
lval eval_op(const lval x, const char* op, const lval y);

#endif
