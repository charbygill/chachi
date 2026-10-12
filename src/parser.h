#ifndef CHACHI_PARSER_H
#define CHACHI_PARSER_H

#include "ast.h"
#include "intern.h"

Ast* parse(const char* src, Interner* i);

#endif
