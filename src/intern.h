#ifndef CHACHI_INTERN_H
#define CHACHI_INTERN_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    size_t len;
    uint32_t hash;
    char chars[];
} InternEntry;

typedef struct {
    InternEntry** entries;
    size_t count;
    size_t capacity;
} Interner;

void interner_init(Interner *i);
void interner_free(Interner *i);
const InternEntry* intern(Interner* i, const char* s, size_t len);

#endif 
