CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -g -fsanitize=address,undefined
LDFLAGS = -fsanitize=address,undefined

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)
DEP = $(OBJ:.o=.d)

chachi: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build chachi

-include $(DEP)

.PHONY: clean
