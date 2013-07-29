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

void ThirdBuyStrategy (const int fd, const int key, const int money,
                       struct Tickets* tickets, struct Company* companies) {
    int buy_list[5] = {1, 3, 4, 6, 8};
    int each_budget = money / 5;

    for (int i = 0; i < 5; i++) {
        Buy(each_budget / getStockPrice(buy_list[i], companies), key, buy_list[i], fd, companies, tickets);
    }
}


/*
以下は現時点(2013/07/18 11:59)でのサーバー側の不具合をついた戦略

購入株数をうまく調整してやると1ターン目から一度も売らずに株を購入し続けることができる。
たとえ所持金がマイナスだとしても。
id 0が全ての会社に対する行動が反映されることが分かっているので、
この購入の連続によって株価が指数関数的に上昇する。
ターンの早い段階でid 0及びその他の株を多数保持しておくことで、
実質の資産が水増しされる。

ゲーム終了時に全保有株を清算して終了することを利用して、
このタイミングで全ての株を精算。
大きくマイナスに振れていた所持金が一気に大きくプラスになる。

上記の戦略について、細かな購入株数の調整のためにAimBugStrategy1~3までが存在し、
ターン進行でこれらを切り替えていく。
*/

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

/*
以下の関数は、2013/7/28現在、恐らく存在するであろうサーバー側の問題点をつくための関数。
(現時点でサーバー側が未だSellの実装にエラーがあるため確認できず。)
リクエストが成立しない場合でもそのリクエストが株価の変動に影響を与える可能性をつこうとしている。
はじめから1社に対して集中的に売却リクエスト、株価が0に落ち込んだ段階でuint32_tの最大値分購入、
少しでも価格が上昇した時点で全て売却して終了
*/

void AimBugStrategy_ver2 (const int fd, const int key, const int money,
                          struct Tickets* tickets, struct Company* companies) {
    static int state;
    if (state == 0) {
        if (companies[7].stock_price <= 0) {
            Buy(UINT32_MAX, key, 7, fd, companies, tickets);
            state = 1;
        } else {
            for (int i = 0; i < 5; i++) {
                Sell(UINT32_MAX, key, 7, fd, companies, tickets);
            }
        }
    } else if (state == 1) {
        if (companies[7].stock_price > 0) {
            Sell(UINT32_MAX, key, 7, fd, companies, tickets);
            state = 2;
        } else {
            state = 1;
        }
    } else if (state == 2) {
        printf("ore no game wa owari da\n");
    } else {
        printf("nanika ga matigatte iru zo!!\n");
    }
}
