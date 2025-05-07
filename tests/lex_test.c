#include <string.h>
#include "lex.h"
#include "onetest.h"
#include "tests.h"

int test_token_array_create(void) {
    Token_array t = Token_array_create();
    assert_num_eq(t.capacity, 8);
    assert_num_eq(t.size, 0);
    Token_array_destroy(&t);
    return 0;
}

int test_token_array_destroy(void) {
    Token_array t = Token_array_create();
    Token_array_append(&t, (Token){TOK_BUILTIN, strdup("Hello")});

    assert_num_eq(t.size, 1);
    Token_array_destroy(&t);

    assert_num_eq(t.capacity, 8);
    assert_num_eq(t.size, 0);
    return 0;
}

int test_token_array_append(void) {
    Token_array t = Token_array_create();
    Token_array_append(&t, (Token){TOK_KEYWORD, strdup("int")});
    Token_array_append(&t, (Token){TOK_FUNCTION, strdup("main")});

    assert_num_eq(t.size, 2);
    assert_str_eq(t.items[0].value, "int");
    assert_str_eq(t.items[1].value, "main");
    Token_array_destroy(&t);
    return 0;
}

int test_lex(void) {
    return 0;
}
