#include "client.h"

int main(int argc, char const *argv[])
{
    int fd; // ファイルディスクリプタ。サーバーとの接続
    uint32_t r_buf[DATA_NUM];

    const char *host = argv[1]; // 第一引数 ex) localhost
    const char *service = argv[2]; // 第二引数 ex) 1111

    /* サーバーとの接続 */
    fd = get_stream(host, service);
    if (fd == -1)
    {
        printf("get_stream error!!\n");
        exit(-1);
    }

    /* 一回目のデータ取得 */
    int len = -1;

    len = getData(fd, r_buf);

    /* ゲームに必要なデータの初期化 */
    struct Company companies[COMPANY_NUM];
    struct Tickets* tickets = InitTickets();
    uint32_t key, tmp_key, tmp_code;
    int money = 10000;
    int state = 0;

    key = InitCompanies(r_buf, companies);

    /* メインルーチン。ターン数分実行される */
    for (int t = 0; t < TURNS; t++) {

        PrintPrices(companies);
        // printf("%d\n", money);

        /* strategy部分 */
        // int comp = 2;
        // if (t % 2 == 0) {
        //   Buy(80, key, comp, fd, companies, tickets);
        // } else if (t % 2 == 1) {
        //   Sell(80, key, comp, fd, companies, tickets);
        // }

        // InitStrategy(fd, key, tickets, companies);
        if (t < 15) {
            AimBugStrategy1(fd, key, money, tickets, companies);
        } else if (t < 35) {
            AimBugStrategy2(fd, key, money, tickets, companies);
        } else {
            AimBugStrategy3(fd, key, money, tickets, companies);
        }

        /* ターン内で投げたリクエストに対する反応を取得する */
        state = 0;
        // stateでゲームの進行状況を管理
        // state 0: 同一ターン内
        // state 1: 次のターンに進行
        // state 2: ゲーム終了。結果の出力へ
        while (state == 0) {

            getData(fd, r_buf);

            // dumpBuf(r_buf);

            tmp_code = 0;
            tmp_key = 0;
            tmp_key = getKey(r_buf);
            if (key != tmp_key) {
                state = 1;
            }
            tmp_code = getCode(r_buf);
            if (tmp_code == REQ_ACCEPT) {
                int accepted_idx = isContain(MakeTicketFromBuf(r_buf), tickets);
                if (accepted_idx != -1) {
                    money += ApplyTicket(accepted_idx, tickets, companies);
                }
            } else if (tmp_code == UNKOWN_CODE || tmp_code == INVALID_KEY ||
                       tmp_code == TOO_MUCH_REQ || tmp_code == ID_NOT_EXIST ||
                       tmp_code == TOO_MUCH_BUY || tmp_code == TOO_MUCH_SELL) {
                int rejected_idx = isContain(MakeTicketFromBuf(r_buf), tickets);
                if (rejected_idx != -1) {
                    DeleteTicket(rejected_idx, tickets);
                }
            } else if (tmp_code == TURN_START) {
                key = Parse(r_buf, companies);
                state = 1;
            } else if (tmp_code == GAME_END) {
                state = 2;
            } else {
            }
        }

        if (state == 2) {
            break;
        }

    }

    printf("\n\n\n");
    printf("##################################\n");
    printf("##############RESULT##############\n");
    printf("##################################\n\n");

    printf("your rank: %d\n", getID(0, r_buf));
    printf("your budget: %u\n", getValue(0, r_buf));

    close(fd);

    return 0;
}
