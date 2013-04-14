CC = gcc

release:
	$(CC) server.c sockets.c -o server
	$(CC) client.c sockets.c -o client
	$(CC) -c -fPIC sockets.c -o sockets.o
	$(CC) -shared -Wl,-soname,libsockets.so.1 -o libsockets.so.1.0.0 sockets.o

debug:
	$(CC) server.c sockets.c -o server -g -Wall
	$(CC) client.c sockets.c -o client -g -Wall
	$(CC) -g -c -fPIC sockets.c -o sockets.o
	$(CC) -g -shared -Wl,-soname,libsockets.so.1 -o libsockets.so.1.0.0 sockets.o
