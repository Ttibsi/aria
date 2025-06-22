#include <print>

#include "vm/aria.h"

int main() {
    aria::VM ariaVM {};
    ariaVM.parse_string("var foo: int = 69;");
    return 0;
}
