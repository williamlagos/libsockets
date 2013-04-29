#include "utils.h"
#include "sockets.h"

int main(int argc, char **argv)
{
	if(argc < 3) error("Uso: client hostname porta\n");
	int socket = create_socket(IPV6,UDP);
	struct sockaddr_in6 address = ipv6_address(argv[1],atoi(argv[2]));
	struct sockaddr_in6 client_address = ipv6_address("",atoi(argv[2]));
	char* buffer = read_input(256);
	bind_socket(&socket,(struct sockaddr*)&client_address);
	send_socket(&socket,(struct sockaddr*)&address,buffer);
	recv_socket(&socket,(struct sockaddr*)&address,buffer);
	/*connect_socket(&socket,(struct sockaddr*)&address);
	write(socket,buffer,255);
	read(socket,buffer,255);*/
	printf("Lido do servidor: %s",buffer);
	return 0;
}
