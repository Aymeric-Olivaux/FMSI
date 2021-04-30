CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -pedantic -g -fsanitize=address -Isrc\

OBJS = \
       src/cc/rohDePollard.o \

BIN = rohDePollard

#TEST_SUITE
TEST_LDLIBS = -lcriterion \

TEST_LDFLAGS = -Wl,-rpath,.

TEST_OBJS = src/tests/test.o \
	    $(OBJS)

all: $(BIN)


$(BIN): $(OBJS)
	$(CC) src/main.cc $^ -o $@ $(CFLAGS)

check: testsuite
	./testsuite --verbose -j1

testsuite: $(TEST_OBJS)
	$(LINK.o) $^ $(TEST_LDFLAGS) $(TEST_LDLIBS) -o $@


clean:
	$(RM) $(OBJS) testsuite $(TEST_OBJS) $(BIN)
.PHONY: all clean
