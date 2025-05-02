CC := clang
CFLAGS := -Wall -Wextra -Wimplicit-fallthrough -g
BIN := aria

ifeq (1, 1)
	san := -fsanitize=address,undefined
endif

sources := $(wildcard src/*.c)
objects := $(patsubst src/%.c,build/%.o,$(sources))

.PHONY: all
all: $(BIN)

build:
	mkdir build

build/%.o: src/%.c | build
	$(CC) $< -c -MMD -MP -o $@ $(CFLAGS) $(san)

$(BIN): $(objects)
	$(CC) $^ -o $@ $(san)

.PHONY: test
test:
	@echo "Tests TBD"

.PHONY: clean
clean:
	rm -rf build
	if [ -f $(BIN) ]; then rm $(BIN); fi
	if [ -f core ]; then rm core; fi

-include $(objects:.o=.d)
