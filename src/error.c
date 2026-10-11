#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdnoreturn.h>

#include "error.h"

noreturn void erxit(int err, const char* msg, ...){
    va_list args;
    va_start(args, msg);

    vfprintf(stderr, msg, args);
    fputc('\n', stderr);
    va_end(args);

    exit(err);
}
