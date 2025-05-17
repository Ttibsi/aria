#define ONETEST_IMPLEMENTATION
#include "onetest.h"

#include "test_collector.h"

int main() {
    return onetest_exec({{
        call(test_token_to_str),
        call(test_lexer_tokenizer),
        call(test_lexer_is_number),
        call(test_lexer_is_builtin),
    }});
}
