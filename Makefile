all: server_udp client_udp

server_udp: server_udp.o
	gcc server_udp.o -o server_udp

server_udp.o: server_udp.c udpsc.h
	gcc -c server_udp.c

client_udp: client_udp.o
	gcc client_udp.o -o client_udp

client_udp.o: client_udp.c udpsc.h
	gcc -c client_udp.c

clean:
	rm -rf *o hello
	