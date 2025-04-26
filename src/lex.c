#include "lex.h"
#include "definitions.h"
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

void lex(Token_array *t, char *contents, size_t contents_len) {
  char text[64];
  text[0] = '\0';
  size_t text_len = 0;

  for (size_t i = 0; i < contents_len; i++) {
    text[text_len] = contents[i];
    text[++text_len] = '\0';

    // Keyword
    for (size_t j = 0; j < Keywords_len; j++) {
      if (strcmp(Keywords[j], text) == 0) {
        Token_array_append(t, (Token){TOK_KEYWORD, strdup(text)});
      }
    }
  }
}
