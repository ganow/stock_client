#include "client.h"

struct Ticket* NewTicket(const uint32_t key, const enum Deal deal,
                         const int id, const int stock_price,
                         const int stock_num) {
    struct Ticket* rtn = (struct Ticket*)malloc(sizeof(struct Ticket));
    if (rtn == NULL) {
        printf("malloc() fail\n");
        exit(-1);
    }
    rtn->key = key;
    rtn->deal = deal;
    rtn->id = id;
    rtn->stock_price = stock_price;
    rtn->stock_num = stock_num;
    return rtn;
}

void PrintTicket(const struct Ticket* t) {
    printf("##Ticket##\n");
    printf("addr: %p\n", t);
    printf("key: %u\n", t->key);
    if (t->deal == BUY) {
        printf("deal: BUY\n");
    } else if (t->deal == SELL) {
        printf("deal: SELL\n");
    } else {
        printf("deal: ERROR\n");
    }
    printf("id: %u\n", t->id);
    printf("stock_price: %u\n", t->stock_price);
    printf("stock_num: %u\n", t->stock_num);
}

void PrintTickets(const struct Tickets* tickets) {
    printf("##Tickets##\n");
    for (int i = 0; i < tickets->available_num; i++) {
        PrintTicket(tickets->list[i]);
        printf("\n");
    }
}

struct Tickets* InitTickets() {
    struct Tickets* rtn = (struct Tickets*)malloc(sizeof(struct Tickets));
    rtn->available_num = 0;
    for (int i = 0; i < TICKETS_MAX; i++) {
        rtn->list[i] = NULL;
    }
    return rtn;
}

void Push (struct Ticket* t, struct Tickets* tickets) {
    if (tickets->list[tickets->available_num] != NULL) {
        printf("error, available_num is incompatible with actual list\n");
        exit(-1);
    }
    // printf("before\n");
    // PrintTickets(tickets);
    tickets->list[tickets->available_num] = t;
    tickets->available_num += 1;
    // printf("after\n");
    // PrintTickets(tickets);
    // printf("finish push\n");
}

void DeleteTicket(const int idx, struct Tickets* tickets) {
    free(tickets->list[idx]);
    for (int i = idx; i < tickets->available_num-1; i++) {
        tickets->list[i] = tickets->list[i+1];
    }
    tickets->list[tickets->available_num-1] = NULL;
    tickets->available_num -= 1;
}

int isEqual (const struct Ticket* t1, const struct Ticket* t2) {
    if (t1->key == t2->key && t1->deal == t2->deal &&
        t1->id == t2->id && t1->stock_price == t2->stock_price &&
        t1->stock_num == t2->stock_num) {
        return 1;
    } else {
        return 0;
    }
}

int isContain(struct Ticket* t, const struct Tickets* tickets) {
    for (int i = 0; i < tickets->available_num; i++) {
        if (isEqual(t, tickets->list[i])) {
            free(t);
            return i;
        }
    }
    printf("There aren't such kind of ticket\n");
    PrintTicket(t);
    return -1;
}
