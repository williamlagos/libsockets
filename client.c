#include "sockets.h"

void
connect_socket
(int* socket_file,
 struct sockaddr_in server_addr)
{
	int fd = *socket_file;
	int status = connect(fd,(struct sockaddr*) &server_addr,
	   		 sizeof(server_addr));
	if(status < 0) error("ERRO ao conectar");
}

char*
readfrom_input
(int buffer_size)
{
	char* buffer = (char*) malloc(buffer_size);
	puts("Por favor, entre com a mensagem: ");
	bzero(buffer,buffer_size-1);
	fgets(buffer,buffer_size-1,stdin);
	return buffer;
}

int 
main(int argc, char **argv)
{
	if(argc < 3) error("Uso: client hostname porta\n");
	int socket = create_socket();
	struct sockaddr_in address = 
	build_address(argv[1],atoi(argv[2]));
	connect_socket(&socket,address);
	char* buffer = readfrom_input(255);
	puts("AAAA");
	writeto_socket(&socket,buffer);
	readfrom_socket(&socket,256);
	return 0;
}
