#include<stdio.h>
#include<stdlib.h>
#define forever while(1)
#define TRUE 1
#define FALSE 0
#define BOOL int
#define STRING void*
#define DEFAULT_SIZE 256

void error(const char *msg);
char* read_input(int buffer_size);
