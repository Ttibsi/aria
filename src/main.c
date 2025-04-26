#include <stdio.h>

#include "lex.h"

int main(int argc, char **argv) {
  if (argc == 2) {
    FILE *f = fopen(argv[1], "r");
    if (!f) {
      return 1;
    }

    fseek(f, 0, SEEK_END);
    int fsize = ftell(f);
    rewind(f);

    char *contents = (char *)malloc(sizeof(char) * fsize);
    int content_size = 0;

    while (content_size < fsize) {
      content_size += fread(contents + content_size, 1, fsize, f);
    }

    fclose(f);

    Token_array toks;
    Token_array_create(&toks);
    lex(&toks, contents, content_size);

    Token_array_print(&toks);
  }
  return 0;
}
