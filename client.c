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
    while (len == -1) {
      len = read(fd, message, sizeof(message));
      printf("reading...\n");
    }
    printf("finish read\n");
    printf("len: %d\n", len);

    printf("%s\n", message);

    /* はじめに送られてくるリストでcompaniesを初期化 */
    len = -1;
    while (len == -1) {
        len = read(fd, r_buf, sizeof(r_buf));
        printf("waiting init list...\n");
    }

    struct Company companies[COMPANY_NUM];
    uint32_t key;

    key = InitCompanies(r_buf, companies);

    PrintCompanies(companies);

    close(fd);

    return 0;
}
