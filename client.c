#include "client.h"

int main(int argc, char const *argv[])
{
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

    for (int i = 0; i < 22; i++) {
        printf("read num: %u\n", buf[i]);
        int num = ntohl(buf[i]);
        printf("num = %u\n", num);
    }

    // /* 送られてきたkeyに学籍番号を足して送信 */
    // num += 71146957;
    // num = htonl(num);
    // len = -1;
    // while (len == -1) {
    //   len = write(fd, &num, sizeof(num));
    // }

    // /* 学籍番号を送信 */
    // len = -1;
    // num = htonl(71146957);
    // while (len == -1) {
    //   len = write(fd, &num, sizeof(num));
    // }

    // /* うまく行ったかどうかの確認 */
    // len = -1;
    // while (len == -1) {
    //   len = read(fd, &buf, BUFSIZE);
    // }
    // num = ntohl(buf);
    // if (num == 0x41434345) {
    //   printf("accepted!!\n");
    // } else {
    //   printf("failed!!\n");
    // }

    close(fd);

    return 0;
}
