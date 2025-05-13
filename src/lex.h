#ifndef LEXER_H
#define LEXER_H

#include <format>
#include <sstream>
#include <string>
#include <vector>

enum class Token_type {
    BUILTIN,
    COLON,
    FUNCTION,
    IDENTIFIER,
    KEYWORD,
    LBRACE,
    LBRACKET,
    LPAREN,
    NUMERIC_LITERAL,
    RBRACE,
    RBRACKET,
    RPAREN,
    SEMI,
    STRING_LITERAL,
};

struct Token {
    Token_type tok;
    std::string value;

    Token(Token_type t, std::string s) : tok(t), value(s) {}
};

std::string token_to_str(Token_type);

struct Lexer {
    std::vector<Token> Tokens = {};

    Lexer(const std::string&);
    [[nodiscard]] bool is_number(const std::string&);
};

template <>
struct std::formatter<Lexer> {
    template <class ParseContext>
    constexpr ParseContext::iterator parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <class FmtContext>
    FmtContext::iterator format(Lexer l, FmtContext& ctx) const {
        std::ostringstream out;

        for (auto&& t : l.Tokens) {
            out << token_to_str(t.tok) << " (\x1b[90m" << t.value << "\x1b[0m)\n";
        }

        return std::ranges::copy(std::move(out).str(), ctx.out()).out;
    }
};

#endif  // LEXER_H
