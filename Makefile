# CC = $(HOME)/local/bin/gcc
CC = /usr/bin/gcc
CFLAGS = -O3 -Wall -std=c99 -I/usr/include -D_POSIX_C_SOURCE=200112L

BASE_SOURCE = comm.c tickets.c companies.c trade.c strategy.c

BINARY = client
SOURCE = client.c

DO_NOTHING = do_nothing
DO_NOTHING_SOURCE = do_nothing.c

TEST = test
TEST_SOURCE = price_watch.c

ATTACK_V1 = attack_v1
ATTACK_V1_SOURCE = main_attack_v1.c

BUYSELL = buysell
BUYSELL_SOURCE = main_buysell.c

AIMBUG_V1 = aimbug_v1
AIMBUG_V1_SOURCE = main_aimbug_v1.c

AIMBUG_V2 = aimbug_v2
AIMBUG_V2_SOURCE = main_aimbug_v2.c

AIMBUG_V2_WITH_ATTACK_V2 = aimbug_v2_with_attack_v2
AIMBUG_V2_WITH_ATTACK_V2_SOURCE = main_aimbug_v2_with_attack_v2.c

all: $(BINARY) $(TEST) $(DO_NOTHING) $(ATTACK_V1) $(BUYSELL) \
	 $(AIMBUG_V1) $(AIMBUG_V2) $(AIMBUG_V2_WITH_ATTACK_V2)

$(BINARY): $(SOURCE)
	$(CC) $(CFLAGS) $(BASE_SOURCE) $(SOURCE) -o $(BINARY)

$(TEST): $(TEST_SOURCE)
	$(CC) $(CFLAGS) $(BASE_SOURCE) $(TEST_SOURCE) -o $(TEST)

$(DO_NOTHING): $(DO_NOTHING_SOURCE)
	$(CC) $(CFLAGS) $(BASE_SOURCE) $(DO_NOTHING_SOURCE) -o $(DO_NOTHING)

$(ATTACK_V1): $(ATTACK_V1_SOURCE)
	$(CC) $(CFLAGS) $(BASE_SOURCE) $(ATTACK_V1_SOURCE) -o $(ATTACK_V1)

$(BUYSELL): $(BUYSELL_SOURCE)
	$(CC) $(CFLAGS) $(BASE_SOURCE) $(BUYSELL_SOURCE) -o $(BUYSELL)

$(AIMBUG_V1): $(AIMBUG_V1_SOURCE)
	$(CC) $(CFLAGS) $(BASE_SOURCE) $(AIMBUG_V1_SOURCE) -o $(AIMBUG_V1)

$(AIMBUG_V2): $(AIMBUG_V2_SOURCE)
	$(CC) $(CFLAGS) $(BASE_SOURCE) $(AIMBUG_V2_SOURCE) -o $(AIMBUG_V2)

$(AIMBUG_V2_WITH_ATTACK_V2): $(AIMBUG_V2_WITH_ATTACK_V2_SOURCE)
	$(CC) $(CFLAGS) $(BASE_SOURCE) $(AIMBUG_V2_WITH_ATTACK_V2_SOURCE) -o $(AIMBUG_V2_WITH_ATTACK_V2)

clean:
	\rm *~ $(BINARY) $(TEST) $(DO_NOTHING) $(ATTACK_V1) $(BUYSELL) \
	$(AIMBUG_V1) $(AIMBUG_V2) $(AIMBUG_V2_WITH_ATTACK_V2)
