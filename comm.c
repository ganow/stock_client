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

uint32_t Parse (const uint32_t* buf, struct Company* companies) {
    uint32_t key = ntohl(buf[0]);
    for (int i = 0; i < COMPANY_NUM; i++) {
        companies[i].stock_price = ntohl(buf[2+i*2]);
    }
    return key;
}