#include "client.h"

void Buy (const int stock_num, const int key, const int company_id, const int fd,
          struct Company* companies, struct Tickets* tickets) {

    Push(NewTicket(key, BUY, company_id, companies[company_id].stock_price, stock_num), tickets);
    companies[company_id].hold_stocks += stock_num;

    char w_buf[BUFSIZE];
    uint32_t w_int_buf[4] = {htonl(key), htonl(REQ_BUY), htonl(company_id), htonl(stock_num)};

    for (int i = 0; i < 4; i++) {
      sprintf(w_buf, "%x", w_int_buf[i]);
      write(fd, w_buf, HEX_DIGIT);
    }

    printf("BUY id: %d num: %d price: %d\n", company_id, stock_num, companies[company_id].stock_price);

}

void Sell (const int stock_num, const int key, const int company_id, const int fd,
          struct Company* companies, struct Tickets* tickets) {

    Push(NewTicket(key, SELL, company_id, companies[company_id].stock_price, stock_num), tickets);
    companies[company_id].hold_stocks += stock_num;

    char w_buf[BUFSIZE];
    uint32_t w_int_buf[4] = {htonl(key), htonl(REQ_SELL), htonl(company_id), htonl(stock_num)};

    for (int i = 0; i < 4; i++) {
      sprintf(w_buf, "%x", w_int_buf[i]);
      write(fd, w_buf, HEX_DIGIT);
    }
    printf("SELL id: %d num: %d price: %d\n", company_id, stock_num, companies[company_id].stock_price);

}