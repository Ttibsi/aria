#include "aria.h"

#include <string>
#include <vector>

#include "lexer.h"

namespace aria {

    void VM::parse_string(std::string text) {
        lexer.tokenize(text);
        lexer.print_tokens(text);
    }

}  // namespace aria
