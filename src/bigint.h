#ifndef CHACHI_BIGINT_H
#define CHACHI_BIGINT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct{
    bool neg;
    size_t len;
    uint32_t limbs[];
} BigInt;

BigInt* bigint_from_i64(int64_t v);
void bigint_free(BigInt* b);
void bigint_print(const BigInt* b);
void bigint_print_hex(const BigInt* b);

#endif
