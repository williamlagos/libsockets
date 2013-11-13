#include "utils.h"
#include "sockets.h"
#include "structs.h"

int main(int argc, char **argv)
{
	if(argc < 3) error("Uso: client hostname porta\n");
	int socket = create_socket(PACKET,RAW,ETH);
	ethernet_packet(); raw_header();
	ipv4_header("10.32.143.201","10.32.143.255",0);
	icmpv4_header(ICMP_ECHO,0,0);
	/*Header* head = (Header*) malloc(sizeof(Header));
	send_socket(&socket,(Address*)&address,(Header*)head);
	recv_socket(&socket,(Address*)&address,(Header*)head,256);
	printf("Recebido: %c\n",head->opcode);
	close(socket);*/
	return 0;
}
