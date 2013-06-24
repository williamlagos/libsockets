#include "utils.h"
#include "sockets.h"
#include "structs.h"

void		
header_packet
(Header* packet)
{
	packet->opcode = 1;
	packet->padding0 = ' ';
	packet->pkglen = 1;

	packet->ipdst[0] = 0;
	packet->ipdst[1] = 0;
	packet->ipdst[2] = 0;
	packet->ipdst[3] = 0;

	packet->ipsrc[0] = 1;
	packet->ipsrc[1] = 1;
	packet->ipsrc[2] = 1;
	packet->ipsrc[3] = 1;

	packet->srcport = 5001;
	packet->dstport = 5001;
	/*strcpy(packet->clientid,' ');
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
