CC ?= cc
PREFIX ?= /usr/local

CFLAGS += -Isrc -Wall -Werror -Wextra -Wno-unused-parameter
LDFLAGS += -lpthread

LIB = libref.a
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

TESTS_SRC = $(wildcard test/*.c)
TESTS_OBJ = $(TESTS_SRC:.c=.o)
TESTS = $(patsubst %.c,%,$(TESTS_SRC))

.PHONY: clean test


all: $(LIB) $(TESTS)

$(LIB): $(OBJ)
	@echo LD $@
	@ar rcs $@ $<

$(TESTS): $(TESTS_OBJ) $(LIB)
	@echo LD $@
	@$(CC) $(CFLAGS) -o $@ $@.o $(LIB)

%.o: %.c
	@echo CC $@
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(LIB) $(OBJ) $(TESTS) $(TESTS_OBJ)

test: $(TESTS)
	@sh test/run.sh
