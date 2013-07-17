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