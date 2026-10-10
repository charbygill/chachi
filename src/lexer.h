#ifndef CHACHI_LEXER_H
#define CHACHI_LEXER_H

#include "token.h"

typedef struct {
    const char* curr;
    const char* next;
    int line;
} Lexer;

void lexer_init(Lexer* lx, const char* src);
Token lexer_next(Lexer* ls);

#endif
