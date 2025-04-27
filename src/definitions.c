#include "definitions.h"

const char* Keywords[] = {
    "break",
    "case",
    "class",
    "continue",
    "default",
    "else",
    "enum",
    "export",
    "func",
    "if",
    "import",
    "return",
    "static",
    "switch",
    "var",
    "while"
};

const size_t Keywords_len = sizeof(Keywords) / sizeof(Keywords[0]);

const char* builtins[] = {
    "print"
};

const size_t builtins_len = sizeof(builtins) / sizeof(builtins[0]);

const char *tok_to_str(Token_type tok) {
    switch (tok) {
    case TOK_KEYWORD: return "KEYWORD";
    case TOK_IDENTIFIER: return "IDENTIFIER";
    case TOK_NUMERIC_LITERAL: return "NUMERIC";
    case TOK_FUNCTION: return "FUNCTION";
    case TOK_STRING_LITERAL: return "STRING";
    case TOK_BUILTIN: return "BUILTIN";
    }
}
