CC := clang
CFLAGS := -Wall -Wextra -Wimplicit-fallthrough -g
BIN := aria

ifeq (0, 1)
	san := -fsanitize=address,undefined
endif

sources := $(filter-out src/main.c,$(wildcard src/*.c))
objects := $(patsubst src/%.c,build/%.o,$(sources))

.PHONY: all
all: $(BIN)

build:
	mkdir build

build/%.o: src/%.c | build
	$(CC) $< -c -MMD -MP -o $@ $(CFLAGS) $(san)

$(BIN): $(objects) build/main.o
	$(CC) $^ -o $@ $(san)

### Tests
test_sources := $(wildcard tests/*.c)
test_objects := $(patsubst tests/%.c,build/%.o,$(test_sources))

build/%.o: tests/%.c | build
	$(CC) $< -c -MMD -MP -Iinclude -Isrc -o $@ $(CFLAGS) $(san)

build/test_exe: $(objects) $(test_objects) build/test.o
	$(CC) $^ -Isrc -o $@ $(san)

.PHONY: test
test: build/test_exe
	./build/test_exe

.PHONY: clean
clean:
	rm -rf build
	if [ -f $(BIN) ]; then rm $(BIN); fi
	if [ -f core ]; then rm core; fi

-include $(objects:.o=.d)
