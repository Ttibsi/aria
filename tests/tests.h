#ifndef TESTS_H
#define TESTS_H

// definitions_test.c
int test_tok_to_str(void);

// lex_test.c
int test_token_array_create(void);
int test_token_array_destroy(void);
int test_token_array_append(void);
int test_token_array_print(void);
int test_lex(void);

#endif // TESTS_H
