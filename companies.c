#include "client.h"

uint32_t InitCompanies(const uint32_t* buf, struct Company* companies) {
    for (int i = 0; i < COMPANY_NUM; i++) {
        companies[i].hold_stocks = 0;
    }
    return Parse(buf, companies);
}

void PrintCompany(const struct Company* c) {
    printf("##Company##\n");
    printf("id: %d\n", c->id);
    printf("stock_price: %d\n", c->stock_price);
    printf("hold_stocks: %d\n", c->hold_stocks);
}

void PrintCompanies(const struct Company* companies) {
    printf("##COMPANIES##\n\n");
    for (int i = 0; i < COMPANY_NUM; i++) {
        PrintCompany(&companies[i]);
        printf("\n");
    }
}