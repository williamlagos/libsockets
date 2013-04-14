#include "utils.h"
#include "sockets.h"

int main(int argc, char **argv)
{
	if(argc < 3) error("Uso: client hostname porta\n");
	int socket = create_socket();
	struct sockaddr_in address = 
	build_address(argv[1],atoi(argv[2]));
	connect_socket(&socket,address);
	char* buffer = read_input(256);
	write(socket,buffer,255);
	read(socket,buffer,255);
	printf("Lido do servidor: %s",buffer);
	return 0;
}
