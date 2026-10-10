#ifndef CHACHI_TOKEN_H
#define CHACHI_TOKEN_H

typedef enum {
    //Single char
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_ASTERISK,
    TOKEN_SLASH,

    //Literals
    TOKEN_NUMBER,

    //SPECIAL
    TOKEN_EOF,
    TOKEN_ERR,
} TokenType;

typedef struct {
    TokenType type;
    const char* start;
    int length;
    int line;
} Token;

#endif
