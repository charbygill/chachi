#ifndef CHACHI_AST_H
#define CHACHI_AST_H

#include <stdint.h>

#include "intern.h"
#include "token.h"

typedef enum {
    AST_NUMBER,
    AST_UNARY,
    AST_OPERATOR,
} AstType;

typedef struct Ast Ast;

typedef struct {
    TokenType operator;
    const InternEntry* text;
    Ast* child;
} Unary;

typedef struct {
    TokenType operator;
    const InternEntry* text;
    Ast* left;
    Ast* right;
} Operator;

typedef union {
   int64_t integer;
   Unary unary;
   Operator operator;
} AstValue;

struct Ast {
    AstType type;
    int line;
    AstValue value;
};

void ast_free(Ast* a);
Ast* ast_number(int64_t value, int line);
Ast* ast_unary(TokenType t, const InternEntry* text, Ast* child, int line);
Ast* ast_operator(TokenType t, const InternEntry* text, Ast* left, Ast* right, int line);

void ast_print(Ast* a);

#endif
