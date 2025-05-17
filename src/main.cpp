#include <fstream>
#include <print>
#include <string>

#include "lex.h"

int main(int argc, char** argv) {
    if (argc == 2) {
        char ch;
        std::string contents = "";
        std::ifstream ifs(argv[1]);

        while (ifs.get(ch)) {
            contents.push_back(ch);
        }

        Lexer toks = Lexer(contents);
        std::println("{}", toks);
    }
    return 0;
}
