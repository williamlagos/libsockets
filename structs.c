#include "utils.h"
#include "sockets.h"
#include "structs.h"

void		
head_packet
(Header* packet)
{
	strcpy(packet->opcode,'1');
	strcpy(packet->padding0,' ');
	strcpy(packet->pkglen,"12");
	strcpy(packet->ipdst," ");
	strcpy(packet->ipsrc," ");
	strcpy(packet->srcport," ");
	strcpy(packet->dstport," ");
	strcpy(packet->clientid,' ');
	strcpy(packet->crctype,' ');
	strcpy(packet->padding1,"  ");
	strcpy(packet->crc,"    ");
}

void		
conn_packet
(Connection* packet)
{

}

void		
conf_packet
(Confirmation* packet)
{

}

char* 
head_serialize
(Header* serial)
{

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
