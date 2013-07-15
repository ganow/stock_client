#include "client.h"

int main(int argc, char const *argv[])
{
    // uint32_t key[3] = {112, 223, 35};
    // enum Deal d[3] = {BUY, SELL, BUY};
    // int id[3] = {1, 2, 3};
    // int s_price[3] = {10, 100, 2};
    // int s_num[3] = {100, 200, 150};

    // struct Tickets* tickets = InitTickets();

    // // for (int i = 0; i < 3; i++) {
    // //     struct Ticket* t = NewTicket(key[i], d[i], id[i], s_price[i], s_num[i]);
    // //     // PrintTicket(t);

    // //     printf("\n");
    // //     Push(t, tickets);

    // //     // PrintTickets(tickets);
    // // }

    // // PrintTickets(tickets);

    // // int num;

    // // if (num = isContain(NewTicket(key[1], d[1], id[1], s_price[1], s_num[1]), tickets) != -1) {
    // //     PrintTicket(tickets->list[num]);
    // //     printf("num: %d\n", num);
    // // }

    // for (int i = 0; i < 200; i++) {
    //     Push(NewTicket(key[0], d[0], id[0], s_price[0], s_num[0]), tickets);
    // }

    // for (int i = 0; i < 200; i++) {
    //     DeleteTicket(i, tickets);
    // }

    // PrintTickets(tickets);

    int fd; // ファイルディスクリプタ。サーバーとの接続
    uint32_t buf[DATA_NUM];
    // fd = get_stream("nepro.sfc.wide.ad.jp", "32768");

    const char *host = argv[1];
    const char *service = argv[2];

    /* サーバーとの接続 */
    fd = get_stream(host, service);
    if (fd == -1)
    {
        printf("get_stream error!!\n");
        exit(-1);
    }

    /* 送られてくるkeyの取得 */
    int len = -1;
    while (len == -1) {
      len = read(fd, buf, sizeof(buf));
      printf("reading...\n");
    }
    printf("finish read\n");
    printf("len: %d\n", len);

    struct Company companies[COMPANY_NUM];
    uint32_t key;

    key = InitCompanies(buf, companies);

    PrintCompanies(companies);

    printf("\n\nkey: %u\n", key);

    return 0;
}
