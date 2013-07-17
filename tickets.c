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

struct Ticket* MakeTicketFromBuf(const uint32_t *buf) {
    uint32_t key;
    int id, value;

    key = getKey(buf);
    id = ntohl(buf[2]);
    value = ntohl(buf[3]);

    return NewTicket(key, BUY, id, 0, value);

}

struct Tickets* InitTickets() {
    struct Tickets* rtn = (struct Tickets*)malloc(sizeof(struct Tickets));
    rtn->available_num = 0;
    for (int i = 0; i < TICKETS_MAX; i++) {
        rtn->list[i] = NULL;
    }
    return rtn;
}

void PrintTicket(const struct Ticket* t) {
    printf("##Ticket##  ");
    printf("key: %x  ", t->key);
    if (t->deal == BUY) {
        printf("deal: BUY  ");
    } else if (t->deal == SELL) {
        printf("deal: SELL  ");
    } else {
        printf("deal: ERROR  ");
    }
    printf("id: %u  ", t->id);
    printf("stock_price: %u  ", t->stock_price);
    printf("stock_num: %u\n", t->stock_num);
}

void PrintTickets(const struct Tickets* tickets) {
    printf("\n##Tickets##\n");
    for (int i = 0; i < tickets->available_num; i++) {
        PrintTicket(tickets->list[i]);
    }
    printf("####end####\n");
}

const struct Ticket * getTicket (const int idx, const struct Tickets* tickets) {
    return tickets->list[idx];
}

enum Deal getDeal (const struct Ticket* t) {
    return t->deal;
}

int getPrice (const struct Ticket* t) {
    return t->stock_price;
}

int getStockNum (const struct Ticket* t) {
    return t->stock_num;
}

void Push (struct Ticket* t, struct Tickets* tickets) {
    if (tickets->list[tickets->available_num] != NULL) {
        printf("error, available_num is incompatible with actual list\n");
        exit(-1);
    }
    tickets->list[tickets->available_num] = t;
    tickets->available_num += 1;
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
    // if (t1->key == t2->key && t1->deal == t2->deal &&
    //     t1->id == t2->id && t1->stock_num == t2->stock_num) {
    if (t1->key == t2->key &&
        t1->id == t2->id && t1->stock_num == t2->stock_num) {
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
    // printf("There aren't such kind of ticket\n");
    // PrintTicket(t);
    // printf("Now tickets:\n");
    // PrintTickets(tickets);
    free(t);
    return -1;
}

int ApplyTicket(const int idx, struct Tickets* tickets, struct Company* companies) {
    /*
    返り値として、所持金の変化分を返す。
    対応するticketの削除
    companies構造体の中の、対応する所持株数を変更する
    */
    int diff_money = 0;
    struct Ticket* ticket = tickets->list[idx];

    diff_money += getPrice(ticket) * getStockNum(ticket);

    if (getDeal(ticket) == BUY) {
        diff_money *= -1;
        companies[idx].hold_stocks += getStockNum(ticket);
    } else if (getDeal(ticket) == SELL) {
        companies[idx].hold_stocks -= getStockNum(ticket);
    } else {
        printf("something wrong in deal at tickets num: %d\n", idx);
        PrintTickets(tickets);
    }
    DeleteTicket(idx, tickets);
    return diff_money;
}


