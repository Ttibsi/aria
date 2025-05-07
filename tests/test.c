#include "tests.h"

#define ONETEST_IMPLEMENTATION
#include "onetest.h"

int main() {
    onetest_init();

    // definitions_test.c
    call(test_tok_to_str, "test_tok_to_str");

    // lex_test.c
    call(test_token_array_create, "test_token_array_create");
    call(test_token_array_destroy, "test_token_array_destroy");
    call(test_token_array_append, "test_token_array_append");
    call(test_lex, "test_lex");

    onetest_exec();
}
