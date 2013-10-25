#include "utils.h"
#include "sockets.h"
#include "structs.h"

int main(int argc, char **argv)
{
	if(argc < 3) error("Uso: client hostname porta\n");
	int socket = create_socket(IPV6,UDP,DEFAULT);
	IPV6_Address address = ipv6_address(argv[1],atoi(argv[2]));
	IPV6_Address client_address = ipv6_address("",atoi(argv[2]));
	bind_socket(&socket,(Address*)&client_address);
	
	/*char* buffer = read_input(256);
	send_socket(&socket,(Address*)&address,buffer);
	recv_socket(&socket,(Address*)&address,buffer,256);
	printf("Recebido:%s",buffer);*/
	
	/*connect_socket(&socket,(Address*)&address);
	write(socket,buffer,255);
	read(socket,buffer,255);*/

	Header* head = (Header*) malloc(sizeof(Header));
	head->opcode = 'A';
	//head_packet(head);
	send_socket(&socket,(Address*)&address,(Header*)head);
	recv_socket(&socket,(Address*)&address,(Header*)head,256);
	printf("Recebido: %c\n",head->opcode);
	close(socket);
	return 0;
}
