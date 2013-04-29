#include "utils.h"
#include "sockets.h"
#include "structs.h"

int main(int argc, char **argv)
{
	if(argc < 3) error("Uso: client hostname porta\n");
	int socket = create_socket(IPV6,UDP);
	IPV6_Address address = ipv6_address(argv[1],atoi(argv[2]));
	IPV6_Address client_address = ipv6_address("",atoi(argv[2]));
	
	char* buffer = read_input(256);
	bind_socket(&socket,(Address*)&client_address);
	send_socket(&socket,(Address*)&address,buffer);
	recv_socket(&socket,(Address*)&address,buffer);
	
	/*connect_socket(&socket,(Address*)&address);
	write(socket,buffer,255);
	read(socket,buffer,255);*/

	Header* head = (Header*) malloc(sizeof(Header));
	head->opcode = 'A';
	char buf[sizeof(head)];
	memcpy(&buf,&head,sizeof(head));
	send_socket(&socket,(Address*)&address,buf);
	recv_socket(&socket,(Address*)&address,buf);
	memcpy(&head,&buf,sizeof(buf));
	printf("Recebido:%c",head->opcode);
	close(socket);
	return 0;
}
