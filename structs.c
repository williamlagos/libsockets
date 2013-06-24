#include "utils.h"
#include "sockets.h"
#include "structs.h"

void		
header_packet
(Header* packet,
 IPV6_Address* addr_dst,
 IPV6_Address* addr_src)
{
	packet->opcode = 1;
	puts("Pacote de Cabecalho\n");
	packet->padding0 = ' ';
	packet->pkglen = 1;
	puts("Tamanho do pacote: 256 bits");

	char buffer[256];
	inet_ntop(IPV6,&addr_src->sin6_addr,buffer,sizeof(buffer));
	inet_pton(IPV6,buffer,(char*)&packet->ipsrc);
	printf("IP Origem: %s\n",buffer);
	inet_ntop(IPV6,&addr_dst->sin6_addr,buffer,sizeof(buffer));
	inet_pton(IPV6,buffer,(char*)&packet->ipdst);
	printf("IP Destino: %s\n",buffer);
	
	packet->srcport = 5001;//addr_src->sin6_port;
	packet->dstport = 5001;//addr_dst->sin6_port;
	printf("Porta do socket: %hd\n",packet->dstport);
	
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
