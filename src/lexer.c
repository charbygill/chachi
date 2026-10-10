#include <stdbool.h>
#include <string.h>
#include "lexer.h"

void lexer_init(Lexer* lx, const char* src){
    lx->start = src;
    lx->curr = src;
    lx->line = 1;
}

static bool lexer_is_end(Lexer* lx);
static char lexer_curr_char(Lexer* lx);
static char lexer_advance(Lexer* lx);
static void lexer_nl(Lexer* lx);
static void lexer_skip_whitespace(Lexer* lx);
static Token token_cc(Lexer* lx, TokenType t);
static Token token_err(Lexer* lx, const char* msg);
static bool is_digit(char c);

Token lexer_next(Lexer* lx){
    lexer_skip_whitespace(lx);
    lx->start = lx->curr;

    if (lexer_is_end(lx)){
	return token_cc(lx, TOKEN_EOF); 
    }

    char c = lexer_advance(lx);
    
    switch(c){
	case '(': return token_cc(lx, TOKEN_LEFT_PAREN);
	case ')': return token_cc(lx, TOKEN_RIGHT_PAREN);
	case '+': return token_cc(lx, TOKEN_PLUS);
	case '-': return token_cc(lx, TOKEN_MINUS);
	case '*': return token_cc(lx, TOKEN_ASTERISK);
	case '/': return token_cc(lx, TOKEN_SLASH);
	default: return token_err(lx, "Unexpected character");
    }
}

static bool lexer_is_end(Lexer* lx){
    return lexer_curr_char(lx) == '\0';
}

static char lexer_curr_char(Lexer* lx){
    return *lx->curr;
}

static char lexer_advance(Lexer* lx){
    char c = lexer_curr_char(lx);
    lx->curr++;
    return c;
}

static void lexer_nl(Lexer* lx){
    lx->line++;
}

static void lexer_skip_whitespace(Lexer* lx){
    for (;;) {
	char c = lexer_curr_char(lx);
	
	switch(c){
	    case '\n':
		lexer_nl(lx);
		//fall through
	    case ' ':
	    case '\t':
	    case '\r':
		lexer_advance(lx);
		break;
	    default:
		return;
	}
    }
}

static Token token_cc(Lexer* lx, TokenType t){
    return (Token){
	.type = t,
	.start = lx->start,
	.length = (int)(lx->curr - lx->start),
	.line = lx->line,
    };
}

static Token token_err(Lexer* lx, const char* msg){
    return (Token){
	.type = TOKEN_ERR,
	.start = msg,
	.length = (int)strlen(msg),
	.line = lx->line,
    };
}

static bool is_digit(char c){
    return c >= '0' && c <= '9';
}
