#include "utils.h"
#include "sockets.h"

int main(int argc, char** argv)
{
	if(argc < 2) error("Uso: server porta\n");
	char* buffer = (char*) malloc(256);
	int socket = create_socket(IPV6,TCP);
	struct sockaddr_in6 address =
	build_ipv6_address("",atoi(argv[1]));
	int newsocket = listen_socket(
	&socket,(struct sockaddr*)&address);
	read(newsocket,buffer,255);
	printf("Mensagem lida: %s",buffer);
	write(newsocket,buffer,255);
	close(newsocket);
	close(socket);
	return 0;
}
