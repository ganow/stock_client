#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <sys/select.h>
#include <limits.h>

#define BUFSIZE 1024

#define COMPANY_NUM 10
#define DATA_NUM 2 + COMPANY_NUM * 2
#define RESPONSE_SIZE 4
#define DEAL_MAX 5
#define TURNS 60
#define TICKETS_MAX DEAL_MAX * TURNS

/* codes */
#define TURN_START 0x00000000
#define REQ_ACCEPT 0x00000001
#define GAME_END 0x00000002
#define REQ_BUY 0x00000100
#define REQ_SELL 0x00000101

/* errors */
#define UNKOWN_CODE 0x00000400
#define INVALID_KEY 0x00000401
#define TOO_MUCH_REQ 0x00000402
#define ID_NOT_EXIST 0x00000403
#define TOO_MUCH_BUY 0x00000404
#define TOO_MUCH_SELL 0x00000405

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
// ネットワーク関連の関数群

int get_stream(const char *host, const char *service);
int getData(const int fd, uint32_t *buf);
uint32_t Parse (const uint32_t* buf, struct Company* companies);
uint32_t getCode(const uint32_t* buf);
char * getCodeName(const uint32_t code);
uint32_t getKey(const uint32_t* buf);
int getID(const int idx, const uint32_t* buf);
int getValue(const int idx, const uint32_t* buf);
void dumpBuf(const uint32_t* buf);
void Attack(const int fd);
void Attack_ver2(const int fd);
uint32_t randomHash();

/* in tickets.c */
// 購入/売却のリクエスト毎にチケットを発行する
// それらのチケットの作成、管理、適用等を扱う関数群

struct Ticket* NewTicket(const uint32_t key, const enum Deal deal,
                         const int id, const int stock_price,
                         const int stock_num);
struct Ticket* MakeTicketFromBuf(const uint32_t* buf);
struct Tickets* InitTickets();
void PrintTicket(const struct Ticket* t);
void PrintTickets(const struct Tickets* tickets);
const struct Ticket* getTicket(const int idx, const struct Tickets* tickets);
enum Deal getDeal(const struct Ticket* t);
int getPrice(const struct Ticket* t);
int getStockNum(const struct Ticket* t);
void Push(struct Ticket* t, struct Tickets* tickets);
void DeleteTicket(const int idx, struct Tickets* tickets);
int isEqual (const struct Ticket* t1, const struct Ticket* t2);
int isContain(struct Ticket* t, const struct Tickets* tickets);
int ApplyTicket(const int idx, struct Tickets* tickets, struct Company* companies);

/* in companies.c */
// 各社の情報を管理するCompany構造体の管理を扱う関数群

uint32_t InitCompanies(const uint32_t* buf, struct Company* companies);
void PrintCompany(const struct Company* c);
void PrintCompanies(const struct Company* companies);
void PrintPrices(const struct Company* companies);
int getStockPrice(const int idx, const struct Company* companies);

/* in trade.c */
// 購入/売却などサーバーに対するリクエストを扱う関数群
// サーバーへのリクエストとチケットの発行等を全て統一的に扱うことができる

void Buy (const int stock_num, const int key, const int company_id, const int fd,
          struct Company* companies, struct Tickets* tickets);

void Sell (const int stock_num, const int key, const int company_id, const int fd,
           struct Company* companies, struct Tickets* tickets);

/* in strategy.c */
// サーバーから送られてくる情報によって、戦略を決定する関数群
// 最終的にはこれらの関数を呼ぶのみになるようにまとめる

void InitStrategy (const int fd, const int key,
                   struct Tickets* tickets, struct Company* companies);
void SecondStrategy (const int fd, const int key,
                     struct Tickets* tickets, struct Company* companies);
void ThirdBuyStrategy (const int fd, const int key, const int money,
                       struct Tickets* tickets, struct Company* companies);
void AimBugStrategy1 (const int fd, const int key, const int money,
                      struct Tickets* tickets, struct Company* companies);
void AimBugStrategy2 (const int fd, const int key, const int money,
                      struct Tickets* tickets, struct Company* companies);
void AimBugStrategy3 (const int fd, const int key, const int money,
                      struct Tickets* tickets, struct Company* companies);
void AimBugStrategy_ver2 (const int fd, const int key, const int money,
                          struct Tickets* tickets, struct Company* companies);
#endif