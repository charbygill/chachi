CC	= gcc
CFLAGS	= -std=c11 -Wall -Wextra -g -fsanitize=address,undefined

chachi: src/main.c src/lexer.c src/lexer.h src/token.h src/ast.c src/ast.h src/error.c src/error.h src/parser.c src/parser.h src/intern.c src/intern.h
	$(CC) $(CFLAGS) -o chachi src/main.c src/lexer.c src/ast.c src/error.c src/parser.c src/intern.c

clean:
	rm -f chachi

.PHONY: clean
