#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stddef.h>

extern const char* Keywords[];
extern const size_t Keywords_len;

typedef enum {
    TOK_KEYWORD,
    TOK_IDENTIFIER
} Token_type;

const char* tok_to_str(Token_type);

#endif // DEFINITIONS_H
