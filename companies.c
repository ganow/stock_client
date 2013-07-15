#include "client.h"

uint32_t InitCompanies(const char* buf, struct Company* companies) {
    for (int i = 0; i < COMPANY_NUM; i++) {
        companies[i].hold_stocks = 0;
    }

    char tmp_buf[HEX_DIGIT];
    for (int k = 0; k < COMPANY_NUM; k++) {
        for (int i = 0; i < HEX_DIGIT; i++) {
            tmp_buf[i] = buf[HEX_DIGIT*2 + HEX_DIGIT*2*k + i];
        }
        companies[k].id = ntohl(strtol(tmp_buf, NULL, 16));
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