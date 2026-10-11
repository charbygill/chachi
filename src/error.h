#ifndef CHACHI_ERROR_H
#define CHACHI_ERROR_H

#include <stdnoreturn.h>

noreturn void erxit(int err, const char* msg, ...);

#endif
