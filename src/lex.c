#include "lex.h"
#include "definitions.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

Token_array Token_array_create() {
    Token_array t;
    t.capacity = 8;
    t.size = 0;
    t.items = malloc(sizeof(Token) * t.capacity);

    return t;
}

void Token_array_destroy(Token_array* t) {
    for (size_t i = 0; i < t->size; i++) {
        free(t->items[i].value);
    }

    free(t->items);
    t->items = NULL;
    t->size = 0;
}

void Token_array_append(Token_array* t, Token item) {
    if (t->size == t->capacity) {
        t->items = realloc(t->items, t->capacity * GROWTH_FACTOR * sizeof(Token));
        t->capacity = t->size * GROWTH_FACTOR * sizeof(Token);
    }
    t->items[t->size] = item;
    t->size++;
}

void Token_array_print(Token_array* t) {
    for (size_t i = 0; i < t->size; i++) {
        printf("%s: (\x1b[90m%s\x1b[0m)\n", tok_to_str(t->items[i].type), t->items[i].value);
    }
}

int isnumber(const char* str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (!(isdigit(i) || i == '.')) {
            return 0;
        }
    }

    return 1;
}

Token_array lex(char* contents, size_t contents_len) {
    Token_array t = Token_array_create();

    char text[64];
    text[0] = '\0';
    size_t text_len = 0;
    int in_string = 0;

    for (size_t i = 0; i < contents_len - 1; i++) {
        text[text_len] = contents[i];
        text[++text_len] = '\0';

        // Symbols
        if (!in_string) {
            switch (contents[i]) {
                case '{':
                    Token_array_append(&t, (Token){TOK_LBRACE, strdup(text)});
                    text[0] = '\0';
                    text_len = 0;
                    break;
                case '}':
                    Token_array_append(&t, (Token){TOK_RBRACE, strdup(text)});
                    text[0] = '\0';
                    text_len = 0;
                    break;
                case ':':
                    Token_array_append(&t, (Token){TOK_COLON, strdup(text)});
                    text[0] = '\0';
                    text_len = 0;
                    break;
                case ';':
                    Token_array_append(&t, (Token){TOK_SEMI, strdup(text)});
                    text[0] = '\0';
                    text_len = 0;
                    break;
                case '[':
                    Token_array_append(&t, (Token){TOK_LBRACKET, strdup(text)});
                    text[0] = '\0';
                    text_len = 0;
                    break;
                case ']':
                    Token_array_append(&t, (Token){TOK_RBRACKET, strdup(text)});
                    text[0] = '\0';
                    text_len = 0;
                    break;
                case '(':
                    Token_array_append(&t, (Token){TOK_LPAREN, strdup(text)});
                    text[0] = '\0';
                    text_len = 0;
                    break;
                case ')':
                    Token_array_append(&t, (Token){TOK_RPAREN, strdup(text)});
                    text[0] = '\0';
                    text_len = 0;
                    break;
            }
        }

        // string literals
        if (contents[i] == '"') {
            if (in_string) {
                Token_array_append(&t, (Token){TOK_STRING_LITERAL, strdup(text)});
                text[0] = '\0';
                text_len = 0;
                in_string = 0;
                continue;
            } else {
                in_string = 1;
            }

        } else if (isspace(text[0])) {
            text[0] = '\0';
            text_len = 0;

            // function
        } else if (contents[i + 1] == '(') {
            Token_array_append(&t, (Token){TOK_FUNCTION, strdup(text)});
            text[0] = '\0';
            text_len = 0;

        } else if (contents[i + 1] == ' ') {
            // Keyword
            for (size_t j = 0; j < Keywords_len; j++) {
                if (strcmp(Keywords[j], text) == 0) {
                    Token_array_append(&t, (Token){TOK_KEYWORD, strdup(text)});
                    text[0] = '\0';
                    text_len = 0;
                    break;
                }
            }

            if (text_len) {
                // Builtins
                for (size_t j = 0; j < builtins_len; j++) {
                    if (strcmp(builtins[j], text) == 0) {
                        Token_array_append(&t, (Token){TOK_BUILTIN, strdup(text)});
                        text[0] = '\0';
                        text_len = 0;
                        break;
                    }
                }

                if (text_len) {
                    if (isnumber(text)) {
                        Token_array_append(&t, (Token){TOK_NUMERIC_LITERAL, strdup(text)});
                        text[0] = '\0';
                        text_len = 0;
                    }
                }
            }
        }
    }

    return t;
}
