CC = gcc

all:
	$(CC) server.c ipv6.c sockets.c -o server
	$(CC) client.c ipv6.c sockets.c -o client
	$(CC) -c -fPIC ipv6.c -o ipv6.o
	$(CC) -c -fPIC sockets.c -o sockets.o
	$(CC) -shared -Wl,-soname,libsockets.so.1 -o libsockets.so.1.0.0 ipv6.o sockets.o

debug:
	$(CC) server.c sockets.c -o server -g -Wall
	$(CC) client.c sockets.c -o client -g -Wall
	$(CC) -g -c -fPIC sockets.c -o sockets.o
	$(CC) -g -shared -Wl,-soname,libsockets.so.1 -o libsockets.so.1.0.0 sockets.o
