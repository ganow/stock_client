#include "client.h"

uint32_t InitCompanies(const uint32_t* buf, struct Company* companies) {
    for (int i = 0; i < COMPANY_NUM; i++) {
        companies[i].hold_stocks = 0;
    }

    for (int k = 0; k < COMPANY_NUM; k++) {
        companies[k].id = ntohl(buf[2+k*2]);
    }
    return Parse(buf, companies);
}

void PrintCompany(const struct Company* c) {
    printf("##Company##  ");
    printf("id: %d  ", c->id);
    printf("stock_price: %d  ", c->stock_price);
    printf("hold_stocks: %d\n", c->hold_stocks);
}

void PrintCompanies(const struct Company* companies) {
    printf("##COMPANIES##\n\n");
    for (int i = 0; i < COMPANY_NUM; i++) {
        PrintCompany(&companies[i]);
    }
}