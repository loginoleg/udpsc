/*
    UDP Server
    For use:
    udp_server [<port>]
*/

#include "udpsc.h"

int main(int argc, char *argv[])
{
    int sock, length, n;
    socklen_t fromlen;
    struct sockaddr_in server;
    struct sockaddr_in from;
    char buf[BUF_SIZE];
    int session_packets_cnt, all_packets_cnt;

    length = sizeof(server);
    bzero(&server,length);

    if (argc < 2)
    {
	info("You may specify the port. Port set to default -- 12333.");
	server.sin_port = htons(12333);
    }
    else
    {
	if ((atoi(argv[1]) < MIN_PORT) || (atoi(argv[1]) > MAX_PORT))
	{
	    error("ERROR, port must be from 0 to 65535\n");
	}
	else
	{
	    server.sin_port=htons(atoi(argv[1]));
	}
    }
    
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
	error("Opening socket");
    }
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    if (bind(sock, (struct sockaddr *)&server, length) < 0)
    {
	error("Binding");
    }
    fromlen = sizeof(struct sockaddr_in);
    all_packets_cnt = 0;
    session_packets_cnt = 0;
    while (1)
    {
	n = recvfrom(sock, buf, BUF_SIZE, 0, (struct sockaddr *)&from, &fromlen);
	if (n < 0) 
	{
    	    error("recvfrom");
    	}
	else
        {
    	    if(strcmp(buf, "end") == 0)
    	    {
    		all_packets_cnt += session_packets_cnt;
    		printf("Stats:\n");
    		printf("Received packets per session: %d\n", session_packets_cnt);
    		printf("All received packets: %d\n", all_packets_cnt);
    		session_packets_cnt = 0;
		memset(buf, 0, BUF_SIZE*sizeof(char));
    	    }
    	    else
    	    {
		session_packets_cnt++;
		printf("udp packet #%d contains the number: '%s'\n", all_packets_cnt+session_packets_cnt, buf); 
		memset(buf, 0, BUF_SIZE*sizeof(char));
            }
       }
   }
   return 0;
 }

