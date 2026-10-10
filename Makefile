CC	= gcc
CFLAGS	= -std=c11 -Wall -Wextra -g -fsanitize=address,undefined

chachi: src/main.c src/lexer.c src/lexer.h src/token.h
	$(CC) $(CFLAGS) -o chachi src/main.c src/lexer.c

clean:
	rm -f chachi

.PHONY: clean
