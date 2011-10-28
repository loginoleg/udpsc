/*
    UDP Client
    For use:
    udp_client <host> [<port> <number_of_packets>]
    Example:
    udp_client myhost.ru 33333 1000
    udp_client myhost.ru
    udp_client myhost.ru 12345
*/

#include "udpsc.h"

int main(int argc, char *argv[])
{
    int sock, n, i, packets_cnt;
    unsigned int length;
    struct sockaddr_in server, from;
    struct hostent *hp;
    char buffer[BUF_SIZE];

    if (argc < 3)
    {
	info("You may specify the port. Port set to default -- 12333");
	server.sin_port = htons(DEF_PORT);
    }
    else
    {
	if ((atoi(argv[2]) < MIN_PORT) || (atoi(argv[2]) > MAX_PORT))
	{
	    error("Error: port must be from 0 to 65535.\n");
	}
	else
	{
	    server.sin_port = htons(atoi(argv[2]));
	}
    }

    if (argc == 4)
    {
	packets_cnt = atoi(argv[3]);
    }
    else
    {
	packets_cnt = DEF_PACKETS_CNT;
    }

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
	error("Openning socket");
    }
    server.sin_family = AF_INET;
    hp = gethostbyname(argv[1]);
    if (hp == 0)
    {
	error("Unknown host");
    }
    bcopy((char *)hp->h_addr, (char *)&server.sin_addr, hp->h_length);
    length = sizeof(struct sockaddr_in);
    for (i = 0; i <= packets_cnt; i++)
    {
	bzero(buffer, BUF_SIZE);
	memset(buffer, 0, BUF_SIZE*sizeof(char));
	snprintf(buffer, BUF_SIZE, "%d", i);
	n = sendto(sock,buffer, strlen(buffer),0,(const struct sockaddr *)&server,length);
	if (n < 0)
	{
	    error("Sendto");
	}
    }
    snprintf(buffer, BUF_SIZE, "end");
    n = sendto(sock,buffer, strlen(buffer),0,(const struct sockaddr *)&server,length);

    close(sock);
    return 0;
}
