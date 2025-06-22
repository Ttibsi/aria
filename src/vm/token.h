#ifndef ARIA_TOKEN_H
#define ARIA_TOKEN_H

#include <array>
#include <cstdint>
#include <string_view>

namespace aria {

    enum class TokenType : std::uint8_t {
        KEYWORD,
        IDENTIFIER,
        COLON,
        TYPE,
        ASSIGN_EQ,
        NUMBER,
        END_STMT,
    };

    std::string token_name(TokenType tok) {
        switch (tok) {
            using enum TokenType;
            case KEYWORD:
                return "KEYWORD";
            case IDENTIFIER:
                return "IDENTIFIER";
            case COLON:
                return "COLON";
            case TYPE:
                return "TYPE";
            case ASSIGN_EQ:
                return "ASSIGN_EQ";
            case NUMBER:
                return "NUMBER";
            case END_STMT:
                return "END_STMT";
        }
    }

    struct TokenPattern {
        const TokenType tok;
        const std::string_view re;

        TokenPattern(TokenType tok, std::string_view re) : tok(tok), re(re) {}
    };

    const std::array<TokenPattern, 7> tokenPatterns = std::array {
        TokenPattern(
            TokenType::KEYWORD,
            "\\b(break|case|class|continue|default|else|enum|export|func|if|import|return|static|"
            "switch|var|while)\\b"),
        TokenPattern(TokenType::IDENTIFIER, "\\b[a-zA-Z][a-zA-Z0-9_]+"),
        TokenPattern(TokenType::COLON, ":"),
        TokenPattern(TokenType::TYPE, "\\b(int|bool|char|str)\\b"),
        TokenPattern(TokenType::ASSIGN_EQ, "=(?!=)"),
        TokenPattern(TokenType::NUMBER, "[\\d]+"),
        TokenPattern(TokenType::END_STMT, ";")};

    struct Token {
        TokenType type;
        int start;
        int end;
    };

}  // namespace aria

#endif  // ARIA_TOKEN_H
