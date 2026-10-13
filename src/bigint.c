#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "bigint.h"
#include "error.h"

static BigInt* bigint_cc(size_t n);
static void bigint_norm(BigInt* b);

BigInt* bigint_from_i64(int64_t v){
    BigInt* b = bigint_cc(2);

    uint64_t mag = v < 0 ? 0u - (uint64_t)v : (uint64_t)v;
    b->limbs[0] = (uint32_t)mag;            //low 32 bits
    b->limbs[1] = (uint32_t)(mag >> 32);    //high 32 bits
    b->neg = v < 0;

    bigint_norm(b);
    return b;
}

void bigint_free(BigInt* b){
    free(b);
}

void bigint_print(const BigInt* b){
    if (b->len == 0){
        printf("0");
        return;
    }

    if (b->neg) printf("-");

    uint64_t r = 0;
    for (size_t i = b->len; i-- > 0;){
        //TODO: print the number
    }
}

void bigint_print_hex(const BigInt* b){
    if (b->len == 0){
        printf("0x0");
        return;
    }

    if (b->neg) printf("-");
    printf("0x%x", b->limbs[b->len-1]);
    for (size_t i = b->len - 1; i-- > 0;){
        printf("%08x", b->limbs[i]);    
    }
}

static BigInt* bigint_cc(size_t n){
    BigInt* b = calloc(1, sizeof(BigInt) + n * sizeof(uint32_t));

    if (b == NULL) {
	erxit(1, "Failed to allocate BigInt");
    }

    b->len = n;

    return b;
}

static void bigint_norm(BigInt* b){
    for (;;) {
        if (b->len == 0){
            b->neg = false;
            return;
        } else if (b->limbs[b->len-1] == 0) {
            b->len--;
        } else return;
    }
}
