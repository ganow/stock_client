#include "client.h"

void Buy (const int stock_num, const int key, const int company_id, const int fd,
          struct Company* companies, struct Tickets* tickets) {

    Push(NewTicket(key, BUY, company_id, companies[company_id].stock_price, stock_num), tickets);
    companies[company_id].hold_stocks += stock_num;

    char w_buf[BUFSIZE];
    sprintf(w_buf, "%x%x%x%x", htonl(key), htonl(REQ_BUY),
                               htonl(company_id), htonl(stock_num));
    write(fd, w_buf, sizeof(w_buf));

    printf("BUY id: %d num: %d price: %d\n", company_id, stock_num, companies[company_id].stock_price);

}

void Sell (const int stock_num, const int key, const int company_id, const int fd,
          struct Company* companies, struct Tickets* tickets) {

    Push(NewTicket(key, SELL, company_id, companies[company_id].stock_price, stock_num), tickets);
    companies[company_id].hold_stocks += stock_num;

    char w_buf[BUFSIZE];
    sprintf(w_buf, "%x%x%x%x", htonl(key), htonl(REQ_SELL),
                               htonl(company_id), htonl(stock_num));
    write(fd, w_buf, sizeof(w_buf));

    printf("SELL id: %d num: %d price: %d\n", company_id, stock_num, companies[company_id].stock_price);

}