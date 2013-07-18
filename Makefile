# CC = $(HOME)/local/bin/gcc
CC = /usr/bin/gcc
CFLAGS = -O3 -Wall -std=c99 -I/usr/include -D_POSIX_C_SOURCE=200112L

BINARY = client
SOURCE = comm.c tickets.c companies.c trade.c strategy.c client.c

DO_NOTHING = do_nothing
DO_NOTHING_SOURCE = comm.c tickets.c companies.c trade.c strategy.c do_nothing.c

TEST = test
TEST_SOURCE = comm.c tickets.c companies.c trade.c strategy.c price_watch.c

all: $(BINARY) $(TEST) $(DO_NOTHING)

$(BINARY): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(BINARY)

$(TEST): $(TEST_SOURCE)
	$(CC) $(CFLAGS) $(TEST_SOURCE) -o $(TEST)

$(DO_NOTHING): $(DO_NOTHING_SOURCE)
	$(CC) $(CFLAGS) $(DO_NOTHING_SOURCE) -o $(DO_NOTHING)

clean:
	\rm *~ $(BINARY) $(TEST) $(DO_NOTHING)
