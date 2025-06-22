CC := clang++
CFLAGS := -Wall -Wextra -std=c++23 -g
ARCHIVE := libaria.a
BIN := aria

ifeq (0, 1)
	san := -fsanitize=address,undefined
endif

sources := $(wildcard src/vm/*.cpp)
objects := build/$(patsubst %.cpp,%.o,$(notdir $(sources)))

.PHONY: all
all: $(BIN)
	...

build:
	mkdir -p build

build/%.o: src/vm/%.cpp | build
	$(CC) $< -c -MMD -MP -o $@ $(CFLAGS) $(san)

build/main.o: src/main.cpp | build
	$(CC) $< -c -MMD -MP -o $@ $(CFLAGS) $(san)

archive: $(objects) | build
	ar -crs build/$(ARCHIVE) $(objects)

.DEFAULT_GOAL := $(BIN)
$(BIN): build/main.o | archive
	$(CC) build/main.o build/$(ARCHIVE) -o $@ $(san)

.PHONY: test
test:
	@echo "Tests TBD"

.PHONY: clean
clean:
	rm -rf build
	if [ -f $(BIN) ]; then rm $(BIN); fi
	if [ -f core ]; then rm core; fi

-include $(objects:.o=.d)
