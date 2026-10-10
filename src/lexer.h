#ifndef CHACHI_LEXER_H
#define CHACHI_LEXER_H

#include "token.h"

typedef struct {
    const char* start;
    const char* curr;
    int line;
} Lexer;

void lexer_init(Lexer* lx, const char* src);
Token lexer_next(Lexer* ls);

#endif
