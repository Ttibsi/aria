#include "lex.h"
#include <algorithm>
#include <cctype>
#include "definitions.h"

std::string token_to_str(Token_type tok) {
    switch (tok) {
        case Token_type::KEYWORD: return "KEYWORD";
        case Token_type::IDENTIFIER: return "IDENTIFIER";
        case Token_type::NUMERIC_LITERAL: return "NUMERIC";
        case Token_type::FUNCTION: return "FUNCTION";
        case Token_type::STRING_LITERAL: return "STRING";
        case Token_type::BUILTIN: return "BUILTIN";
        case Token_type::LBRACE: return "LBRACE";
        case Token_type::RBRACE: return "RBRACE";
        case Token_type::COLON: return "COLON";
        case Token_type::SEMI: return "SEMI";
        case Token_type::LBRACKET: return "LBRACKET";
        case Token_type::RBRACKET: return "RBRACKET";
        case Token_type::LPAREN: return "LPAREN";
        case Token_type::RPAREN: return "RPAREN";
    };

    return "";
}

// TODO: Escaped literals
Lexer::Lexer(const std::string& contents) {
    std::string text = "";
    bool in_string = false;

    for (auto&& c : contents) {
        text.push_back(c);

        // symbols
        if (!in_string) {
            switch (c) {
                case '{':
                    Tokens.push_back({Token_type::LBRACE, std::to_string(c)});
                    break;
                case '}':
                    Tokens.push_back({Token_type::RBRACE, std::to_string(c)});
                    break;
                case ':':
                    Tokens.push_back({Token_type::COLON, std::to_string(c)});
                    break;
                case ';':
                    Tokens.push_back({Token_type::SEMI, std::to_string(c)});
                    break;
                case '[':
                    Tokens.push_back({Token_type::LBRACKET, std::to_string(c)});
                    break;
                case ']':
                    Tokens.push_back({Token_type::RBRACKET, std::to_string(c)});
                    break;
                case '(':
                    Tokens.push_back({Token_type::FUNCTION, text.substr(0, text.size() - 1)});
                    Tokens.push_back({Token_type::LPAREN, std::to_string(c)});
                    break;
                case ')':
                    Tokens.push_back({Token_type::RPAREN, std::to_string(c)});
                    break;
                case '"':
                    in_string = true;
                    break;
            };

            text = "";
            continue;
        }

        if (c == '"') {
            Tokens.push_back({Token_type::STRING_LITERAL, text});
            continue;
        }

        if (std::isspace(c)) {
            text = text.substr(text.size() - 1);
            if (std::find(keywords.begin(), keywords.end(), text) != keywords.end()) {
                Tokens.push_back({Token_type::KEYWORD, text});
            } else if (std::find(builtins.begin(), builtins.end(), text) != builtins.end()) {
                Tokens.push_back({Token_type::BUILTIN, text});
            } else if (is_number(text)) {
                Tokens.push_back({Token_type::NUMERIC_LITERAL, text});
            }

            text = "";
            continue;
        }
    }
}

[[nodiscard]] bool Lexer::is_number(const std::string& text) {
    std::string acceptable = "0123456789.xbo";
    for (auto&& c : text) {
        if (acceptable.find(c) == std::string::npos) {
            return false;
        }
    }

    return true;
}
