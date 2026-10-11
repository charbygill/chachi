#include <stdlib.h>

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

Ast* ast_unary(TokenType u, Ast* child, int line){
    return ast_new(AST_UNARY, (AstValue){
        .unary={ 
	    .operator = u,
	    .child = child,
	},
    }, line);
}

Ast* ast_operator(TokenType u, Ast* left, Ast* right, int line){
    return ast_new(AST_OPERATOR, (AstValue){
        .operator={ 
	    .operator = u,
	    .left = left,
	    .right = right,
	},
    }, line);
}
