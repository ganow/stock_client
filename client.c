#include "client.h"

int main(int argc, char const *argv[])
{
    int fd; // ファイルディスクリプタ。サーバーとの接続
    char message[BUFSIZE];
    char r_buf[BUFSIZE];
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

    /* 接続の確立 */
    int len = -1;
    while (len <= 0) {
      len = read(fd, message, sizeof(message));
      printf("reading...\n");
    }
    printf("finish read\n");
    printf("len: %d\n", len);

    printf("%s\n", message);

    /* はじめに送られてくるリストでcompaniesを初期化 */
    len = -1;
    while (len < 0) {
        len = read(fd, r_buf, sizeof(r_buf));
        printf("waiting init list...\n");
    }
    printf("finish read\n");
    printf("len: %d\n", len);
    dumpBuf(r_buf);

    struct Company companies[COMPANY_NUM];
    struct Tickets* tickets = InitTickets();
    uint32_t key;

    key = InitCompanies(r_buf, companies);

    PrintCompanies(companies);

    for (int t = 0; t < TURNS; t++) {

        printf("%d th turn\n", t);

        if (t == 0) {
            Buy(10, key, 0, fd, companies, tickets);
        } else if (t == 1) {
            Sell(10, key, 0, fd, companies, tickets);
        }

        int state = 0;

        while (state == 0) {

            len = -1;
            while (len <= 0) {
                len = read(fd, r_buf, sizeof(r_buf));
                printf("waiting init list...\n");
            }

            dumpBuf(r_buf);

            uint32_t code;
            uint32_t tmp_key;
            tmp_key = getKey(r_buf);
            if (key != tmp_key) {
                state = 1;
                printf("next turn\n");
            }
            // code = getCode(r_buf);
            // if (code == REQ_ACCEPT) {
            //     //
            // } else if (code == UNKOWN_CODE || code == INVALID_KEY ||
            //            code == TOO_MUCH_REQ || code == ID_NOT_EXIST ||
            //            code == TOO_MUCH_BUY || code == TOO_MUCH_SELL) {
            //     printf("code error type: %x\n", code);
            // } else if (code == TURN_START) {
            //     key = Parse(r_buf, companies);
            //     state = 1;
            // } else {
            //     printf("something wrong in code\n");
            // }
        }

    }

    close(fd);

    return 0;
}
