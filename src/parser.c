#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "parser.h"
#include "lexer.h"
#include "token.h"
#include "error.h"

typedef struct {
    Lexer lx;
    Token curr;
    Token prev;
} Parser;

static void parser_init(Parser *p, const char* src);
static void parser_advance(Parser* p);
static bool parser_check(Parser* p, TokenType type);
static void parser_expect(Parser* p, TokenType type, const char* msg);

static Ast* parse_expression(Parser* p);
static Ast* parse_token(Parser* p);
static int64_t parse_int(Token t);

typedef struct ParseStack ParseStack;
struct ParseStack {
    Ast* this;
    ParseStack* prev;
};

static ParseStack* parse_stack_cc(Ast* root){
    ParseStack* stack = malloc(sizeof(ParseStack));
    stack->this = root;
    stack->prev = 0;
    return stack;
}

static void parse_stack_free(ParseStack* stack){
    if (stack == 0) return;
    ParseStack* prev = stack->prev;
    free(stack);
    stack = prev;
}

static void parse_stack_push(ParseStack* stack, Ast* node){
    ParseStack* next = malloc(sizeof(ParseStack));
    next->this = node;
    next->prev = stack->prev;
    stack->prev = next;
}

static Ast* parse_stack_pop(ParseStack* stack){
    if (stack->prev == 0) return 0;
    ParseStack* top = stack->prev;
    Ast* node = top->this;
    stack->prev = top->prev;
    free(top);
    return node;
}

Ast* parse(const char* src){
    Parser p;
    parser_init(&p, src);
    Ast* a = parse_expression(&p);
    parser_expect(&p, TOKEN_EOF, "Expected end of input");
    return a;
}

static void parser_init(Parser *p, const char* src){
    lexer_init(&p->lx, src);
    parser_advance(p); 
}

static void parser_advance(Parser* p){
    p->prev = p->curr;
    p->curr = lexer_next(&p->lx);
    if (p->curr.type == TOKEN_ERR) erxit(1, "line %d: '%.*s'", p->curr.line, p->curr.length, p->curr.start); 
}

static bool parser_check(Parser* p, TokenType type){
    return (p->curr.type == type);
}

static void parser_expect(Parser* p, TokenType type, const char* msg){
    if (parser_check(p, type)){
        parser_advance(p);
        return;
    }
    erxit(1, "line %d: %s", p->curr.line, msg);
}

static Ast* parse_expression(Parser* p){ //This is the ast build loop, need a stack to push tokens onto
    Ast* root = 0;
    ParseStack* stack = parse_stack_cc(root);

    ParseStack* branch = 0;

    for (;;) {
        if (parser_check(p, TOKEN_EOF)) break;
        Ast* next = parse_token(p);

        
        //temp
        root = next;
    }
    
    return root;
}

static Ast* parse_token(Parser* p){ //Token 
    switch (p->curr.type) {
        case TOKEN_NUMBER:
            parser_advance(p);
            return ast_number(parse_int(p->prev), p->prev.line);
        default:
            erxit(1, "line %d: Unexpected token '%.*s'", p->curr.line, p->curr.length, p->curr.start);
    }
}

static int64_t parse_int(Token t){
    int64_t value = 0;

    for (int i = 0; i < t.length; i++) {
        int d = t.start[i] - '0';

        if (value > (INT64_MAX - d) / 10) {
            erxit(1, "line %d: Number too large: %.*s", t.line, t.length, t.start);
        }

        value = value * 10 + d;
    }
    return value;
}
