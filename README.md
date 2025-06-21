# Aria

An embeddable programming language built on a bytecode VM

### How to use
Prerequisites: `Make`, a c++23-compatible compiler (by default clang)

```console
make archive
```
This will build the static library you need to include - `build/libaria.a`. You
also just have to point your include path to `src/vm` or include
`src/vm/aria.h` in your repo. Set the `CC` variable to set your chosen
compiler, or set a path to the given compiler: `make CC=g++ archive`.

```console
make
```
will build an executable binary `aria` which acts as a REPL
