#include "utils.h"
#include "sockets.h"
#include "structs.h"

Header*		
head_deserialize
(const char* serial)
{

}

Connection*	
conn_deserialize
(const char* serial)
{

}

Confirmation*	
conf_deserialize
(const char* serial)
{

}
char* 
head_serialize
(Header* serial)
{
	char serialized[48];
	serialized[0] = serial->opcode;
	serialized[1] = serial->padding0;
	serialized[2] = serial->pkglen;
	int i = 4;
	for(;i < 20; i++) serialized[i] = serial->ipdst[i-4];
	for(;i < 36; i++) serialized[i] = serial->ipsrc[i-20];
	serialized[36] = serial->srcport;
	serialized[38] = serial->dstport;
	serialized[39] = serial->clientid;
	serialized[40] = serial->crctype;
	serialized[41] = serial->padding0;
}

char* 
conn_serialize
(Connection* serial)
{

}

char* 
conf_serialize
(Confirmation* serial)
{

}
