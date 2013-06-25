#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define forever while(1)

#define INVALID_HEADER_OPCODE		0x800
#define INVALID_PKGLEN				0x801
#define INVALID_DESTINATION_IP		0x802
#define INVALID_SOURCE_IP			0x803
#define INVALID_SOURCE_PORT			0x804
#define INVALID_DESTINATION_PORT	0x805
#define INVALID_CLIENT_ID			0x806
#define INVALID_CRC_TYPE			0x807
#define INVALID_CRC_VALUE			0x808
#define INVALID_OPCODE				0x809
#define INVALID_WINDOWSIZE			0x80A
#define INVALID_FILENAME			0x80B

#define CRC_POLYNOM 0x296;

#define ESTABLISHED 1
#define REJECTED 2
#define ERROR 4

#define ESTABLISH 1
#define CLOSE 2

void error(const char *msg,int exitcode);
void logto(const char *type,const char *msg);
char* read_input(int buffer_size);
