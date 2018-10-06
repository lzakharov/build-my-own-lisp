#include "ltype.h"

#include "lval.h"

char* ltype_name(lval_t t) {
 switch(t) {
    case LVAL_NUM: return "Number";
    case LVAL_SYM: return "Symbol";
    case LVAL_ERR: return "Error";
    case LVAL_STR: return "String";
    case LVAL_FUN: return "Function";
    case LVAL_SEXPR: return "S-Expression";
    case LVAL_QEXPR: return "Q-Expression";
    default: return "Unknown";
  }
}
