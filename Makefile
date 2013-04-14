CC = gcc

all:
	$(CC) server.c -o server
	$(CC) client.c -o client

debug:
	$(CC) server.c -o server -g -Wall
	$(CC) client.c -o client -g -Wall
