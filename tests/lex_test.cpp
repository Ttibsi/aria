#include <ranges>
#include <string>
#include <vector>

#include "lex.h"
#include "onetest.h"
#include "test_collector.h"

int test_token_to_str() {
    assert_eq(token_to_str(Token_type::KEYWORD), std::string("KEYWORD"));
    assert_eq(token_to_str(Token_type::IDENTIFIER), std::string("IDENTIFIER"));
    assert_eq(token_to_str(Token_type::NUMERIC_LITERAL), std::string("NUMERIC"));
    assert_eq(token_to_str(Token_type::FUNCTION), std::string("FUNCTION"));
    assert_eq(token_to_str(Token_type::STRING_LITERAL), std::string("STRING"));
    assert_eq(token_to_str(Token_type::BUILTIN), std::string("BUILTIN"));
    assert_eq(token_to_str(Token_type::LBRACE), std::string("LBRACE"));
    assert_eq(token_to_str(Token_type::RBRACE), std::string("RBRACE"));
    assert_eq(token_to_str(Token_type::COLON), std::string("COLON"));
    assert_eq(token_to_str(Token_type::SEMI), std::string("SEMI"));
    assert_eq(token_to_str(Token_type::LBRACKET), std::string("LBRACKET"));
    assert_eq(token_to_str(Token_type::RBRACKET), std::string("RBRACKET"));
    assert_eq(token_to_str(Token_type::LPAREN), std::string("LPAREN"));
    assert_eq(token_to_str(Token_type::RPAREN), std::string("RPAREN"));
    assert_eq(token_to_str(Token_type::EOF_), std::string("EOF"));

    return 0;
}

int test_lexer_tokenizer() {
    std::string text = "func main() { print(\"Hello world\"); })";
    Lexer lex = Lexer(text);
    std::vector<Token> expected = {
        {Token_type::KEYWORD, "func"},
        {Token_type::FUNCTION, "main"},
        {Token_type::LPAREN, "("},
        {Token_type::RPAREN, ")"},
        {Token_type::LBRACE, "{"},
        {Token_type::BUILTIN, "print"},
        {Token_type::LPAREN, "("},
        {Token_type::STRING_LITERAL, "Hello world"},
        {Token_type::RPAREN, ")"},
        {Token_type::SEMI, ":"},
        {Token_type::RBRACE, "}"},
    };

    for (const auto [idx, token] : std::views::enumerate(lex.Tokens)) {
        assert_eq(token.tok, expected.at(idx).tok);
        assert_eq(token.value, expected.at(idx).value);
    }

    return 0;
}

int test_lexer_is_number() {
    Lexer l = Lexer("");

    assert_eq(l.is_number("1337"), true);
    assert_eq(l.is_number("leet"), false);

    // hex
    assert_eq(l.is_number("0x45"), true);
    assert_eq(l.is_number("0xbabecafe"), true);
    assert_eq(l.is_number("babecafe"), false);

    // octal
    assert_eq(l.is_number("0o33"), true);
    assert_eq(l.is_number("0o99"), false);

    // binary
    assert_eq(l.is_number("0b00010010"), true);
    assert_eq(l.is_number("0b2"), false);

    return 0;
}
