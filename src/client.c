#include "utils.h"
#include "sockets.h"
#include "structs.h"

int main(int argc, char **argv)
{
	Header* head;
	SOCKET socket;
	char* buffer = malloc(256);
	IPV4_Address address,client_address;
	if(argc < 3) error("Uso: client hostname porta\n");
	socket = create_socket(IPV4,TCP,DEFAULT);
	address = ipv4_address(argv[1],atoi(argv[2]));
	client_address = ipv4_address("",atoi(argv[2]));
	bind_socket(&socket,(Address*)&client_address);
	
	buffer = read_input(256);
	connect_socket(&socket,(Address*)&address);
	write(socket,buffer,255);
	read(socket,buffer,255);
	printf("Recebido:%s",buffer);

	/*head = (Header*) malloc(sizeof(Header));
	send_socket(&socket,(Address*)&address,(Header*)head);
	recv_socket(&socket,(Address*)&address,(Header*)head,256);
	printf("Recebido: %c\n",head->opcode);*/
	close(socket);
	return 0;
}
