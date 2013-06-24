#include "utils.h"
#include "sockets.h"
#include "structs.h"

int main(int argc, char** argv)
{
	IPV6_Address address;
	void* buffer = (void*) malloc(256);
	if(argc < 2) error("Uso: server porta [interface]\n",1);
	else if(argc > 2) address = ipv6_ifaddress(argv[2],atoi(argv[1]));
	else address = ipv6_address("",atoi(argv[1]));
	int socket = create_socket(IPV6,UDP);
	bind_socket(&socket,(Address*)&address);
	forever{
		recv_socket(&socket,(Address*)&address,buffer,256);
		unpack_header((Header*) buffer,&address,atoi(argv[1]));
		send_socket(&socket,(Address*)&address,buffer,256);
	}
	/*int newsocket = listen_socket(
	&socket,(struct sockaddr*)&address);
	read(newsocket,buffer,255);
	write(newsocket,buffer,255);
	close(newsocket);*/
	close(socket);
	return 0;
}
