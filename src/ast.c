#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "ast.h"
#include "error.h"

void ast_free(Ast* a){
    if (a == NULL) return;

    switch (a->type){
	case AST_NUMBER:
	    break;
	case AST_UNARY:
            ast_free(a->value.unary.child);
	    break;
	case AST_OPERATOR:
            ast_free(a->value.operator.left);
            ast_free(a->value.operator.right);
	    break;
    }
    free(a);
}

static Ast* ast_new(AstType type, AstValue value, int line){
    Ast *a = malloc(sizeof *a);
    if (a == NULL) {
	erxit(1, "Failed to allocate ast node");
    }

    *a = (Ast){
	.type = type,
	.line = line,
	.value = value,
    };
    return a;
}

Ast* ast_number(int64_t value, int line){
    return ast_new(AST_NUMBER, (AstValue){.integer = value}, line);
}

Ast* ast_unary(Token u, Ast* child, int line){
    //assert(u.type == ...);
    return ast_new(AST_UNARY, (AstValue){
        .unary={ 
	    .operator = u,
	    .child = child,
	},
    }, line);
}

Ast* ast_operator(Token u, Ast* left, Ast* right, int line){
    assert(
        u.type == TOKEN_PLUS        ||
        u.type == TOKEN_MINUS       ||
        u.type == TOKEN_ASTERISK    ||
        u.type == TOKEN_SLASH
    );
    return ast_new(AST_OPERATOR, (AstValue){
        .operator={ 
	    .operator = u,
	    .left = left,
	    .right = right,
	},
    }, line);
}

void ast_print(Ast* a){
    if (a == NULL) return;
    
    switch (a->type){
	case AST_NUMBER:
            printf("%lld", (long long)a->value.integer);
	    break;
	case AST_UNARY:
	    break;
	case AST_OPERATOR: {
            printf("(");
            Token op = a->value.operator.operator;
            printf("'%.*s' ", op.length, op.start);
            ast_print(a->value.operator.left);
            printf(" ");
            ast_print(a->value.operator.right);
            printf(")");
	    break;
        }
    }
}
