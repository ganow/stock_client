# CC = $(HOME)/local/bin/gcc
CC = /usr/bin/gcc
CFLAGS = -Wall -std=c99 -I/usr/include -D_POSIX_C_SOURCE=200112L

BINARY = client
SOURCE = comm.c tickets.c companies.c trade.c strategy.c client.c

TEST = test
TEST_SOURCE = comm.c tickets.c companies.c trade.c strategy.c price_watch.c

all: $(BINARY) $(TEST)

$(BINARY): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(BINARY)

$(TEST): $(TEST_SOURCE)
	$(CC) $(CFLAGS) $(TEST_SOURCE) -o $(TEST)

clean:
	\rm *~ $(BINARY) $(TEST)
