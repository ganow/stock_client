#include "client.h"

// key fd companies tickets

/* 戦略メモ

株価の変動をいかにして推定するか？
極端な話、いっこ前の状態に大きく依存するはず
なぜなら他のプレーヤーは一つ前の状態を見てリクエストを出す
→ 予めリクエストがスケジューリングされていた場合はわからない

さかのぼった時刻も加味した判断をすれば、さらに予測精度は向上する

*/

void InitStrategy (const int fd, const int key,
                   struct Tickets* tickets, struct Company* companies) {
    int buy_list[5] = {1, 3, 4, 6, 8};
    int each_budget = 10000 / 5;

    for (int i = 0; i < 5; i++) {
        Buy(each_budget / getStockPrice(buy_list[i], companies), key, buy_list[i], fd, companies, tickets);
    }
}

void SecondStrategy (const int fd, const int key,
                     struct Tickets* tickets, struct Company* companies) {
    int buy_list[5] = {1, 3, 4, 6, 8};

    for (int i = 0; i < 5; i++) {
        Sell(companies[buy_list[i]].hold_stocks, key, buy_list[i], fd, companies, tickets);
    }
}

void AimBugStrategy1 (const int fd, const int key, const int money,
                     struct Tickets* tickets, struct Company* companies) {
    int buy_list[5] = {0, 1, 3, 4, 6};
    int each_budget = 0;

    for (int i = 0; i < COMPANY_NUM; i++) {
        each_budget += companies[i].stock_price * companies[i].hold_stocks;
    }
    each_budget += money;
    // each_budget /= 2;
    if (each_budget >= 15000000) {
        each_budget = 15000000;
    }

    printf("each_budget: %d\n", each_budget);

    for (int i = 0; i < 5; i++) {
        Buy(each_budget / getStockPrice(buy_list[i], companies), key, buy_list[i], fd, companies, tickets);
    }
}

void AimBugStrategy2 (const int fd, const int key, const int money,
                     struct Tickets* tickets, struct Company* companies) {
    int buy_list[5] = {0, 1, 3, 4, 6};
    int each_budget = 0;

    for (int i = 0; i < COMPANY_NUM; i++) {
        each_budget += companies[i].stock_price * companies[i].hold_stocks;
    }
    each_budget = 50000;

    printf("each_budget: %d\n", each_budget);

    for (int i = 0; i < 5; i++) {
        Buy(each_budget / getStockPrice(buy_list[i], companies), key, buy_list[i], fd, companies, tickets);
    }
}

void AimBugStrategy3 (const int fd, const int key, const int money,
                     struct Tickets* tickets, struct Company* companies) {
    int buy_list[5] = {0, 1, 3, 4, 6};
    int each_budget = 0;

    for (int i = 0; i < COMPANY_NUM; i++) {
        each_budget += companies[i].stock_price * companies[i].hold_stocks;
    }
    each_budget = 100000;

    printf("each_budget: %d\n", each_budget);

    for (int i = 0; i < 5; i++) {
        Buy(each_budget / getStockPrice(buy_list[i], companies), key, buy_list[i], fd, companies, tickets);
    }
}
