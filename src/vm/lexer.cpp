#include "lexer.h"

#include <cctype>
#include <print>
#include <regex>

namespace aria {

    void Lexer::tokenize(const std::string& text) {
        int start = 0;

        while (start < text.size()) {
            std::string remaining = text.substr(start, text.size() - start);
            if (isspace(remaining.at(0))) {
                start++;
                continue;
            }

            for (auto&& pattern : tokenPatterns) {
                std::smatch match;
                if (std::regex_search(remaining, match, std::regex(pattern.re.data())) &&
                    match.position() == 0) {
                    tokens.emplace_back(pattern.tok, start, start + match.length());
                    start += match.length();
                    break;
                }
            }
        }
    }

    void Lexer::print_tokens(const std::string& text) {
        for (auto&& tok : tokens) {
            std::println(
                "{} - \x1b[90m{}\x1b[0m", token_name(tok.type),
                text.substr(tok.start, tok.end - tok.start));
        }
    }

}  // namespace aria
