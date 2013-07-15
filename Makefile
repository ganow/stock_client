CC = $(HOME)/local/bin/gcc
CFLAGS = -O3 -Wall -std=c99

BINARY = client
SOURCE = comm.c tickets.c companies.c client.c

TEST = test
TEST_SOURCE = comm.c tickets.c companies.c test.c

all: $(BINARY) $(TEST)

$(BINARY): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(BINARY)

$(TEST): $(TEST_SOURCE)
	$(CC) $(CFLAGS) $(TEST_SOURCE) -o $(TEST)

clean:
	\rm *~ $(BINARY) $(TEST)
