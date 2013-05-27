#include "utils.h"
#include "sockets.h"
#include "structs.h"

int main(int argc, char** argv)
{
	if(argc < 2) error("Uso: server porta\n");
	int socket = create_socket(IPV4,UDP);
	IPV6_Address address = ipv6_address("",atoi(argv[1]));
	bind_socket(&socket,(Address*)&address);
	void* buffer = (void*) malloc(256);
	while(1){
		recv_socket(&socket,(Address*)&address,buffer,256);
		Header* head = (Header*) buffer;
		printf("Mensagem lida: %c\n",head->opcode);
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
