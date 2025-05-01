#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include <stdlib.h>

#include "definitions.h"

typedef struct {
    Token_type type;
    char* value;
} Token;

typedef struct {
    Token* items;
    size_t size;
    size_t capacity;
} Token_array;

#define GROWTH_FACTOR 2

void Token_array_create(Token_array*);
void Token_array_destroy(Token_array*);
void Token_array_append(Token_array*, Token);
void Token_array_print(Token_array*);

Token_array lex(char*, size_t);

#endif // LEXER_H
