#include "client.h"

int get_stream(const char *host, const char *service) {
    int error, fd;
    struct addrinfo *ai, *ai0, hints;

    memset((void *)&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family |= PF_UNSPEC;

    error = -1;
    if (error == getaddrinfo(host, service, &hints, &ai0)) {
        fprintf(stderr, "getaddrinfo(%s, %s, ...): %s(%d)\n", host, service, gai_strerror(error), error);
        exit(-1);
    }

    for (ai = ai0; ai0; ai = ai->ai_next) {
        fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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

uint32_t Parse (const char* buf, struct Company* companies) {
    char tmp_buf[HEX_DIGIT];
    uint32_t key;

    for (int i = 0; i < HEX_DIGIT; i++) {
        tmp_buf[i] = buf[i];
    }
    key = ntohl(strtol(tmp_buf, NULL, 16));

    for (int k = 0; k < COMPANY_NUM; k++) {
        for (int i = 0; i < HEX_DIGIT; i++) {
            tmp_buf[i] = buf[HEX_DIGIT*2 + HEX_DIGIT*2*k + HEX_DIGIT + i];
        }
        companies[k].stock_price = ntohl(strtol(tmp_buf, NULL, 16));
    }
    return key;
}

uint32_t getCode (const char* buf) {
    uint32_t code;
    char tmp_buf[HEX_DIGIT];
    for (int i = 0; i < HEX_DIGIT; i++) {
        tmp_buf[i] = buf[HEX_DIGIT + i];
    }
    code = ntohl(strtol(tmp_buf, NULL, 16));
    return code;
}