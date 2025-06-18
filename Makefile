CC := clang++
CFLAGS := -Wall -Wextra -std=c++23 -Wimplicit-fallthrough -g
BIN := aria

ifeq (0, 1)
	san := -fsanitize=address,undefined
endif

sources := $(wildcard src/*.cpp) $(wildcard src/vm/*.cpp)
src_to_obj = build/$(patsubst %.cpp,%.o,$(notdir $1))
objects = $(foreach s,$(sources),$(call src_to_obj,$s))

ifeq ($(filter clean,$(MAKECMDGOALS)),)
$(foreach s,$(sources),\
	$(eval $(call src_to_obj,$s): $s | build ; \
		$(CC) $$< -c -MMD -MP -o $$@ $(CFLAGS) $(san)\
	)\
)
endif

.PHONY: all
all: $(BIN)

build:
	mkdir build

.DEFAULT_GOAL := $(BIN)
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
