CC := clang++
CFLAGS := -Wall -Wextra -Wimplicit-fallthrough -g -std=c++23
BIN := aria

ifeq (0, 1)
	san := -fsanitize=address,undefined
endif

sources := $(filter-out src/main.cpp,$(wildcard src/*.cpp))
objects := $(patsubst src/%.cpp,build/%.o,$(sources))

.PHONY: all
all:
	bear -- $(MAKE) $(BIN)

build:
	mkdir build

build/%.o: src/%.cpp | build
	$(CC) $< -c -MMD -MP -o $@ $(CFLAGS) $(san)

$(BIN): $(objects) build/main.o
	$(CC) $^ -o $@ $(san)

#### Tests
test_sources := $(wildcard tests/*.cpp)
test_objects := $(patsubst tests/%.cpp,build/%.o,$(test_sources))

build/%.o: tests/%.cpp | build
	$(CC) $< -c -MMD -MP -Iinclude -Isrc -o $@ $(CFLAGS) $(san)

build/test_exe: $(objects) $(test_objects)
	$(CC) -Iinclude -Isrc $^ -o $@ $(san)

.PHONY: test
test: build/test_exe
	bear -- $(MAKE) build/test_exe
	./build/test_exe

.PHONY: clean
clean:
	rm -rf build
	if [ -f $(BIN) ]; then rm $(BIN); fi
	if [ -f core ]; then rm core; fi

-include $(objects:.o=.d)
