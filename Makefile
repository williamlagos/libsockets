CC = gcc

all:
	$(CC) main.c -o main
	$(CC) client.c -o client

debug:
	$(CC) main.c -o main -g -Wall
	$(CC) client.c -o client -g -Wall
