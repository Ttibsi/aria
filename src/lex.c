#include "lex.h"
#include "definitions.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

void Token_array_create(Token_array *t) {
    t->capacity = 8;
    t->size = 0;
    t->items = malloc(sizeof(Token) * 8);
}

void Token_array_destroy(Token_array *t) {
    free(t->items);
    t->size = 0;
}

void Token_array_append(Token_array *t, Token item) {
    if (t->size == t->capacity) {
        t->items = realloc(t->items, t->size * GROWTH_FACTOR);
        t->capacity = t->size * GROWTH_FACTOR;
    }
    t->items[t->size] = item;
    t->size++;
}

void Token_array_print(Token_array *t) {
    for (size_t i = 0; i < t->size; i++) {
        printf("%s: (%s)\n", tok_to_str(t->items[i].type), t->items[i].value);
    }
}

int isnumber(const char* str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (!(isdigit(i) || i == '.')) { return 0; }
    }

    return 1;
}

void lex(Token_array *t, char *contents, size_t contents_len) {
    char text[64];
    text[0] = '\0';
    size_t text_len = 0;
    int in_string = 0;

    for (size_t i = 0; i < contents_len; i++) {
        text[text_len] = contents[i];
        text[++text_len] = '\0';

        // string literals
        if (contents[i] == '"') {
            if (in_string) {
                 Token_array_append(t, (Token){TOK_STRING_LITERAL, strdup(text)});
                 text[0] = '\0';
                 text_len = 0;
                 in_string = 0;
                 continue;
            } else {
                 in_string = 1;
            }
        }


        if (isspace(text[0])) {
            text[0] = '\0';
            text_len = 0;

        // next char is a symbol
        } else if (!(isalpha(contents[i + 1]) || isdigit(contents[i + 1]))) {

            // Keyword
            for (size_t j = 0; j < Keywords_len; j++) {
                if (strcmp(Keywords[j], text) == 0) {
                    Token_array_append(t, (Token){TOK_KEYWORD, strdup(text)});
                    text[0] = '\0';
                    text_len = 0;
                    break;
                }
            }
            if (text_len == 0) { continue; }

           // Builtins
           for (size_t j = 0; j < builtins_len; j++) {
               if (strcmp(builtins[j], text) == 0) {
                    Token_array_append(t, (Token){TOK_BUILTIN, strdup(text)});
                    text[0] = '\0';
                    text_len = 0;
                    break;
               }
            }
            if (text_len == 0) { continue; }

            if (isnumber(text)) {
                Token_array_append(t, (Token){TOK_NUMERIC_LITERAL, strdup(text)});
                text[0] = '\0';
                text_len = 0;
            } else if (contents[i + 1] == '(') {
                Token_array_append(t, (Token){TOK_FUNCTION, strdup(text)});
                text[0] = '\0';
                text_len = 0;
            }
        }
    } else {
        switch (contents[i]) {
            case '{':
            case '}':
            case ':':
            case ';':
            case '[':
            case ']':
            case '(':
            case ')':
        }
    }
}
