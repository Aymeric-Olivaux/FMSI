CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -g -fsanitize=address -Isrc\

OBJS = \
       src/c/rohDePollard.o \

BIN = rohDePollard

#TEST_SUITE
TEST_LDLIBS = -lcriterion \

TEST_LDFLAGS = -Wl,-rpath,.

TEST_OBJS = src/tests/test.o \
	    $(OBJS)

all: $(BIN)


$(BIN): $(OBJS)
	$(CC) src/main.c $^ -o $@ $(CFLAGS)

check: testsuite
	./testsuite --verbose -j1

testsuite: $(TEST_OBJS)
	$(LINK.o) $^ $(TEST_LDFLAGS) $(TEST_LDLIBS) -o $@


clean:
	$(RM) $(OBJS) testsuite $(TEST_OBJS) $(BIN)
.PHONY: all clean
