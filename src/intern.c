#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "intern.h"
#include "error.h"

static InternEntry* intern_entry_cc(const char* s, size_t len, uint32_t hash);
static uint32_t hash_string(const char* s, size_t len);
static void interner_grow(Interner* i);

void interner_init(Interner *i){
    size_t starting_capacity = 1 << 3;

    InternEntry** entries = calloc(starting_capacity, sizeof *entries);
    if (entries == NULL) {
	erxit(1, "Failed to allocate intern entries");
    }

    i->entries = entries;
    i->count = 0;
    i->capacity = starting_capacity;
}

void interner_free(Interner *i){
    for (size_t j = 0; j < i->capacity; j++){
        free(i->entries[j]);
    }
    free(i->entries);
}

const InternEntry* intern(Interner* i, const char* s, size_t len){
    if (i->count == i->capacity) erxit(1, "internal error: intern table full");//Should not happen anymore
    else if (i->count + 1 > i->capacity * 3 / 4) interner_grow(i);

    uint32_t hash = hash_string(s, len);
    size_t index = hash & (i->capacity - 1); //Works as long as capacity => 2**n

    InternEntry* e = NULL;
    for (;;) {
        e = i->entries[index];

        if (e == NULL){
            e = intern_entry_cc(s, len, hash);
            i->entries[index] = e;
            i->count++;
            break;
        } else if (
                e->hash == hash &&
                e->len == len   && 
                memcmp(e->chars, s, len) == 0) {
            break;
        } else {
            index = (index + 1) & (i->capacity - 1);//Look above! 
        } 
    }

    return e;
}

static InternEntry* intern_entry_cc(const char* s, size_t len, uint32_t hash){
    InternEntry *i = malloc((sizeof *i) + len + 1);
    if (i == NULL) {
	erxit(1, "Failed to allocate intern entry");
    }

    i->len = len;
    i->hash = hash;

    memcpy(i->chars, s, len);
    i->chars[len]='\0';

    return i;
}

static uint32_t hash_string(const char* s, size_t len){
    uint32_t hash = 2166136261u;
    for (size_t i = 0; i < len; i++){
        hash ^= (unsigned char)s[i];
        hash *= 16777619u;
    } 
    return hash;
}

static void interner_grow(Interner* i){
    size_t new_cap = i->capacity * 2;

    InternEntry** entries = calloc(new_cap, sizeof *entries);
    if (entries == NULL) {
	erxit(1, "Failed to allocate intern entries");
    }

    for (size_t j = 0; j < i->capacity; j++){
        if (i->entries[j] != NULL){
            InternEntry* e = i->entries[j];
            size_t index = e->hash & (new_cap - 1);//Look above*2!
            for (;;) {
                if (entries[index] == NULL){
                    entries[index] = e;
                    break;
                }
                index = (index + 1) & (new_cap - 1);//Look above*3! 
            }
        }
    }
    free(i->entries);

    i->entries = entries;
    i->capacity = new_cap;    
}
