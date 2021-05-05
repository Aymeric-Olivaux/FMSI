CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -pedantic -g -fsanitize=address -Isrc\

#TEST_SUITE
TEST_LDLIBS = -lcriterion \

TEST_LDFLAGS = -Wl,-rpath,.

TEST_OBJS = src/tests/test.o \
	    $(OBJS)

all: alice pollard

alice: 
	$(CC) src/cc/AliceEtBob.cc -o AliceEtBob $(CFLAGS)

pollard:
	$(CC) src/cc/rohDePollard.cc -o rhoDePollard $(CFLAGS)


check: testsuite
	./testsuite --verbose -j1

testsuite: $(TEST_OBJS)
	$(LINK.o) $^ $(TEST_LDFLAGS) $(TEST_LDLIBS) -o $@


clean:
	$(RM)  testsuite AliceEtBob hacked.txt rhoDePollard
.PHONY: all clean
