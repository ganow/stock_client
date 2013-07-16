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

    uint32_t tmp_buf[BUFSIZE];

    while (total_read < DATA_NUM) {
        while (len < 0) {
            len = read(fd, tmp_buf, sizeof(tmp_buf));
        }
        for (int i = 0; i < len; i++) {
            buf[total_read+i] = tmp_buf[i];
        }
        total_read += len;
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

uint32_t getKey (const uint32_t* buf) {
    uint32_t key;
    key = ntohl(buf[0]);
    return key;
}

void dumpBuf (const uint32_t* buf) {
    printf("start to dump buf\n");

    for (int i = 0; i < DATA_NUM; i++) {
        printf("%x\n", ntohl(buf[i]));
    }
}
