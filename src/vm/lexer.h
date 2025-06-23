#ifndef ARIA_LEXER_H
#define ARIA_LEXER_H

#include <string>
#include <vector>

#include "token.h"

namespace aria {
    struct Lexer {
            int index = 0;
            std::vector<Token> tokens = {};

            void tokenize(const std::string&);
            void print_tokens(const std::string&);
    };
}  // namespace aria

#endif  // ARIA_LEXER_H
