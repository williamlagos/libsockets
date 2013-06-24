#include "utils.h"
#include "sockets.h"
#include "structs.h"

void		
header_packet
(Header* packet)
{
	packet->opcode = '1';
/*	strcpy(packet->padding0,' ');
	strcpy(packet->pkglen,"12");
	strcpy(packet->ipdst," ");
	strcpy(packet->ipsrc," ");
	strcpy(packet->srcport," ");
	strcpy(packet->dstport," ");
	strcpy(packet->clientid,' ');
	strcpy(packet->crctype,' ');
	strcpy(packet->padding1,"  ");
	strcpy(packet->crc,"    ");*/
}

void		
connection_packet
(Connection* packet)
{

}

void		
configuration_packet
(Confirmation* packet)
{

}
