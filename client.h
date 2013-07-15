#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 1024

#define COMPANY_NUM 10
#define DATA_NUM 2 + COMPANY_NUM * 2
#define DEAL_MAX 5
#define TURNS 60
#define TICKETS_MAX DEAL_MAX * TURNS

#define HEX_DIGIT 10

/* codes */
#define TURN_START 0x000
#define REQ_ACCEPT 0x001
#define REQ_BUY 0x100
#define REQ_SELL 0x101

/* errors */
#define UNKOWN_CODE 0x400
#define INVALID_KEY 0x401
#define TOO_MUCH_REQ 0x402
#define ID_NOT_EXIST 0x403
#define TOO_MUCH_BUY 0x404
#define TOO_MUCH_SELL 0x405


/* 基本データ型 */

enum Deal { BUY, SELL };

struct Ticket {
  uint32_t key;
  enum Deal deal;
  int id;
  int stock_price;
  int stock_num;
};

struct Tickets {
  struct Ticket* list[TICKETS_MAX];
  int available_num;
};

struct Company {
  int id;
  int stock_price;
  int hold_stocks;
};

/* in comm.c */

int get_stream(const char *host, const char *service);
uint32_t Parse (const char* buf, struct Company* companies);

/* in tickets.c */

struct Ticket* NewTicket(const uint32_t key, const enum Deal deal,
                         const int id, const int stock_price,
                         const int stock_num);
void PrintTicket(const struct Ticket* t);
void PrintTickets(const struct Tickets* tickets);
struct Tickets* InitTickets();
void Push(struct Ticket* t, struct Tickets* tickets);
void DeleteTicket(const int idx, struct Tickets* tickets);
int isEqual (const struct Ticket* t1, const struct Ticket* t2);
int isContain(struct Ticket* t, const struct Tickets* tickets);

/* in companies.c */

uint32_t InitCompanies(const char* buf, struct Company* companies);
void PrintCompany(const struct Company* c);
void PrintCompanies(const struct Company* companies);

#endif