#ifndef ARIA_PUBLIC_H
#define ARIA_PUBLIC_H

#include <string>

#include "lexer.h"

// The public API for the Aria bytecode virtual machine.
namespace aria {
    class VM {
        private:
            Lexer lexer;

        public:
            void parse_string(std::string);
    };
}  // namespace aria

#endif  // ARIA_PUBLIC_H
