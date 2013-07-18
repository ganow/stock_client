#include "client.h"

void Buy (const int stock_num, const int key, const int company_id, const int fd,
          struct Company* companies, struct Tickets* tickets) {

    Push(NewTicket(key, BUY, company_id, companies[company_id].stock_price, stock_num), tickets);

    uint32_t w_int_buf[4] = {htonl(key), htonl(REQ_BUY), htonl(company_id), htonl(stock_num)};
    uint32_t tmp;

    int len = -1;

    for (int i = 0; i < 4; i++) {
      len = -1;
      tmp = w_int_buf[i];
      while (len == -1) {
        len = write(fd, &tmp, sizeof(tmp));
      }
    }

    // printf("BUY id: %d num: %d price: %d\n", company_id, stock_num, companies[company_id].stock_price);

}

void Sell (const int stock_num, const int key, const int company_id, const int fd,
          struct Company* companies, struct Tickets* tickets) {

    Push(NewTicket(key, SELL, company_id, companies[company_id].stock_price, stock_num), tickets);

    uint32_t w_int_buf[4] = {htonl(key), htonl(REQ_SELL), htonl(company_id), htonl(stock_num)};
    uint32_t tmp;

    int len = -1;

    for (int i = 0; i < 4; i++) {
      len = -1;
      tmp = w_int_buf[i];
      while (len == -1) {
        len = write(fd, &tmp, sizeof(tmp));
      }
    }

    // printf("SELL id: %d num: %d price: %d\n", company_id, stock_num, companies[company_id].stock_price);

}