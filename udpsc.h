#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 256
#define DEF_PACKETS_CNT 20
#define DEF_PORT 12333
#define MIN_PORT 0
#define MAX_PORT 65535

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void info(const char *msg)
{
    printf("INFO: %s\n", msg);
}