#include "lex.h"

#include <algorithm>
#include <cctype>
#include <regex>

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
        case Token_type::EOF_: return "EOF";
    };

    return "";
}

// TODO: Escaped literals
Lexer::Lexer(const std::string& contents) {
    Tokens.reserve(16);
    tokenizer(contents);
}

void Lexer::tokenizer(const std::string& contents) {
    std::string text = "";
    bool in_string = false;

    for (auto&& c : contents) {
        text.push_back(c);

        // symbols
        if (!in_string) {
            switch (c) {
                case '{':
                    Tokens.emplace_back(Token_type::LBRACE, std::string(1, c));
                    text = "";
                    continue;
                case '}':
                    Tokens.emplace_back(Token_type::RBRACE, std::string(1, c));
                    text = "";
                    continue;
                case ':':
                    Tokens.emplace_back(Token_type::COLON, std::string(1, c));
                    text = "";
                    continue;
                case ';':
                    Tokens.emplace_back(Token_type::SEMI, std::string(1, c));
                    text = "";
                    continue;
                case '[':
                    Tokens.emplace_back(Token_type::LBRACKET, std::string(1, c));
                    text = "";
                    continue;
                case ']':
                    Tokens.emplace_back(Token_type::RBRACKET, std::string(1, c));
                    text = "";
                    continue;
                case '(':
                    if (is_builtin(text.substr(0, text.size() - 1))) {
                        Tokens.emplace_back(Token_type::BUILTIN, text.substr(0, text.size() - 1));
                    } else {
                        Tokens.emplace_back(Token_type::FUNCTION, text.substr(0, text.size() - 1));
                    }

                    Tokens.emplace_back(Token_type::LPAREN, std::string(1, c));
                    text = "";
                    continue;
                case ')':
                    Tokens.emplace_back(Token_type::RPAREN, std::string(1, c));
                    text = "";
                    continue;
                case '"':
                    in_string = true;
                    continue;
            };
        }

        if (c == '"') {
            Tokens.emplace_back(Token_type::STRING_LITERAL, text);
            text = "";
            in_string = false;
            continue;
        }

        if (std::isspace(c)) {
            if (in_string) {
                continue;
            }

            text = text.substr(0, text.size() - 1);
            if (std::find(keywords.begin(), keywords.end(), text) != keywords.end()) {
                Tokens.emplace_back(Token_type::KEYWORD, text);
            } else if (is_number(text)) {
                Tokens.emplace_back(Token_type::NUMERIC_LITERAL, text);
            }

            text = "";
            continue;
        }
    }
}

[[nodiscard]] bool Lexer::is_number(const std::string& text) {
    std::regex pattern(R"(^\d+$|^0o[0-7]+$|^0b[0-1]+$|^0x[\dabcdefABCDEF]+$)");
    return std::regex_match(text, pattern);
}

[[nodiscard]] bool Lexer::is_builtin(const std::string& text) {
    return std::find(builtins.begin(), builtins.end(), text) != builtins.end();
}
