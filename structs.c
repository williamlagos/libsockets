#include "utils.h"
#include "sockets.h"
#include "structs.h"

void		
header_packet
(Header* packet,
 IPV6_Address* addr_dst,
 IPV6_Address* addr_src,
 int port_num)
{
	char buffer[256],message[256];
	packet->opcode = 1;
	logto("INFO","Enviando pacote de Cabecalho");
	packet->padding0 = ' ';
	packet->pkglen = sizeof(Header)*8;
	sprintf(message,"Tamanho do pacote: %d bits",packet->pkglen);
	logto("INFO",message);

	inet_ntop(IPV6,&addr_src->sin6_addr,buffer,sizeof(buffer));
	inet_pton(IPV6,buffer,&(packet->ipsrc));
	sprintf(message,"IP Origem: %s",buffer);
	logto("INFO",message);
	inet_ntop(IPV6,&addr_dst->sin6_addr,buffer,sizeof(buffer));
	inet_pton(IPV6,buffer,&(packet->ipdst));
	sprintf(message,"IP Destino: %s",buffer);
	logto("INFO",message);
	
	packet->srcport = port_num;
	packet->dstport = port_num;
	sprintf(message,"Porta do socket: %hd",packet->dstport);
	logto("INFO",message);
	
	packet->clientid = ' ';
	packet->crctype = 1;
	packet->padding1 = ' ';
	packet->crc = 0;
	logto("DONE","Pacote cabecalho enviado");
}

void
unpack_header
(Header* packet,
 IPV6_Address* addr,
 int port_num)
{
	char message[256],buffer[256],aux[256];
	bzero(&message,256); bzero(&buffer,256); bzero(&aux,256);
	if(packet->opcode != 1) error("Opcode invalido para cabecalho",INVALID_HEADER_OPCODE);
	logto("INFO","Recebendo pacote de Cabecalho");
	if(packet->pkglen != sizeof(Header)*8) error("Tamanho invalido para o cabecalho",INVALID_PKGLEN);
	sprintf(message,"Tamanho do pacote recebido: %d bits",packet->pkglen);
	logto("INFO",message);
	
	inet_ntop(IPV6,&packet->ipdst,buffer,sizeof(buffer));
	inet_ntop(IPV6,&addr->sin6_addr,aux,sizeof(aux));
	if(strcmp(buffer,aux) != 0) error("Endereco destino nao coincide",INVALID_DESTINATION_IP);
	sprintf(message,"Endereco destino confirmado: %s",buffer);
	logto("INFO",message);
	
	inet_ntop(IPV6,&packet->ipsrc,buffer,sizeof(buffer));
	if(strcmp(buffer,aux) != 0 && strstr(buffer,aux) == NULL) error("Endereco origem nao coincide",INVALID_SOURCE_IP);
	sprintf(message,"Endereco origem confirmado: %s",buffer);
	logto("INFO",message);
	
	if(port_num != packet->srcport) error("Porta de origem nao coincide",INVALID_SOURCE_PORT);
	sprintf(message,"Porta de origem: %hd",packet->srcport);
	logto("INFO",message);	
	if(port_num != packet->srcport) error("Porta de origem nao coincide",INVALID_DESTINATION_PORT);
	sprintf(message,"Porta de destino: %hd",packet->dstport);
	logto("INFO",message);
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
