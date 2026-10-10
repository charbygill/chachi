#ifndef CHACHI_AST_H
#define CHACHI_AST_H

#include <stdint.h>

#include "token.h"

typedef enum {
    AST_NUMBER,
    AST_UNARY,
    AST_OPERATOR,
} AstType;

typedef struct Ast Ast;

typedef struct {
    TokenType operator;
    Ast* child;
} Unary;

typedef struct {
    TokenType operator;
    Ast* left;
    Ast* right;
} Binary;

struct Ast {
    AstType type;
    int line;
    union {
	int64_t integer;
	Unary unary;
	Binary binary;
    } as;
};

#endif
