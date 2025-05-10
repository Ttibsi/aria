#include "definitions.h"
#include "onetest.h"
#include "tests.h"

int test_tok_to_str(void) {
    assert_str_eq(tok_to_str(TOK_KEYWORD), "KEYWORD");
    assert_str_eq(tok_to_str(TOK_IDENTIFIER), "IDENTIFIER");
    assert_str_eq(tok_to_str(TOK_NUMERIC_LITERAL), "NUMERIC");
    assert_str_eq(tok_to_str(TOK_FUNCTION), "FUNCTION");
    assert_str_eq(tok_to_str(TOK_STRING_LITERAL), "STRING");
    assert_str_eq(tok_to_str(TOK_BUILTIN), "BUILTIN");
    assert_str_eq(tok_to_str(TOK_LBRACE), "LBRACE");
    assert_str_eq(tok_to_str(TOK_RBRACE), "RBRACE");
    assert_str_eq(tok_to_str(TOK_COLON), "COLON");
    assert_str_eq(tok_to_str(TOK_SEMI), "SEMI");
    assert_str_eq(tok_to_str(TOK_LBRACKET), "LBRACKET");
    assert_str_eq(tok_to_str(TOK_RBRACKET), "RBRACKET");
    assert_str_eq(tok_to_str(TOK_LPAREN), "LPAREN");
    assert_str_eq(tok_to_str(TOK_RPAREN), "RPAREN");

    return 0;
}
