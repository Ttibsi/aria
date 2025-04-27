#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stddef.h>

extern const char* Keywords[];
extern const size_t Keywords_len;
extern const char* builtins[];
extern const size_t builtins_len;

typedef enum {
    TOK_KEYWORD,
    TOK_IDENTIFIER,
    TOK_NUMERIC_LITERAL,
    TOK_FUNCTION,
    TOK_STRING_LITERAL,
    TOK_BUILTIN,
    TOK_LBRACE,
    TOK_RBRACE,
    TOK_COLON,
    TOK_SEMI,
    TOK_LBRACKET,
    TOK_RBRACKET,
    TOK_LPAREN,
    TOK_RPAREN,
} Token_type;

const char* tok_to_str(Token_type);

#endif // DEFINITIONS_H
