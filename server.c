#include "utils.h"
#include "sockets.h"
#include "structs.h"

int main(int argc, char** argv)
{
	if(argc < 2) error("Uso: server porta\n");
	int socket = create_socket(IPV6,UDP);
	IPV6_Address address = ipv6_address("",atoi(argv[1]));
	char* buffer = (char*) malloc(256);
	Header* head = (Header*) malloc(sizeof(Header));
	bind_socket(&socket,(Address*)&address);
	while(1){
		puts("ABC\n");
		recv_socket(&socket,(Address*)&address,buffer);
		memcpy(&head,&buffer,sizeof(buffer));
		printf("Mensagem lida: %s\n",buffer);
		printf("Enviado: %c\n",head->opcode);
		send_socket(&socket,(Address*)&address,buffer);
	}
	/*int newsocket = listen_socket(
	&socket,(struct sockaddr*)&address);
	read(newsocket,buffer,255);
	write(newsocket,buffer,255);
	close(newsocket);*/
	close(socket);
	return 0;
}
