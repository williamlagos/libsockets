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
	logto("START","Enviando pacote de Cabecalho");
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
	
	packet->clientid = 0;
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
	if(packet->opcode != 1 && packet->opcode != 2 && packet->opcode != 4) error("Opcode invalido para cabecalho",INVALID_HEADER_OPCODE);
	logto("START","Recebendo pacote de Cabecalho");
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
	
	if(packet->clientid > 128) error("ID de cliente invalido",INVALID_CLIENT_ID);
	else if(packet->clientid == 0){
		srand(time(NULL));
		int id = rand()%128+1;
		sprintf(message,"ID de cliente gerado: %d",id);
		logto("INFO",message);
	}
	
	if(packet->crctype != 1) error("Tipo de CRC invalido",INVALID_CRC_TYPE);
	sprintf(message,"Selecionado o algoritmo CRC8 para controle de erros");
	logto("INFO",message);
	
	//int crc = packet->crc;
	logto("DONE","Pacote cabecalho recebido, preparando para subsequente");
}

void		
connection_packet
(Connection* packet,
 int connectype,
 int windowsize,
 char* filename)
{
	packet->opcode = connectype;
	packet->padding = ' ';
	packet->window = windowsize;
	packet->filesize = 0;
	strcpy(packet->filename,filename);
}

void
unpack_connection
(Connection* packet,
 IPV6_Address* addr,
 int port_num)
{
	char message[256],buffer[64];
	if(packet->opcode != 1 && packet->opcode != 2) error("Opcode invalido para conexao",INVALID_OPCODE);
	else if(packet->opcode == 1) strcpy(buffer,"Estabelecendo conexao com o servidor");
	else if(packet->opcode == 2) strcpy(buffer,"Encerrando conexao com o servidor");
	sprintf(message,"%s",buffer);
	logto("START",message);
	
	if(packet->window < 1 || packet->window > 31) error("Tamanho da janela invalido",INVALID_WINDOWSIZE);
	sprintf(message,"Janela deslizante configurada com o tamanho de %d",packet->window);
	logto("INFO",message);
	
	sprintf(message,"Tamanho do arquivo para envio: %d bytes",packet->filesize);
	logto("INFO",message);
	
	if(packet->filename[254] != 0) error("Nome invalido para envio de arquivos",INVALID_FILENAME);
	sprintf(message,"Nome do arquivo para envio: %s",packet->filename);
	logto("INFO",message);
	
	logto("DONE","Conexao estabelecida com o servidor com sucesso");
}

void		
confirmation_packet
(Confirmation* packet,
 int confirmationcode,
 int sequencenumber)
{
	packet->opcode = confirmationcode;
	packet->number = sequencenumber;
}

void		
unpack_confirmation
(Confirmation* packet,
 IPV6_Address* addr,
 int port_num)
{
	
}

void
data_packet
(Data* packet)
{
	
}

void
unpack_data
(Data* packet,
 IPV6_Address* addr,
 int port_num)
{
	
}