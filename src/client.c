#include "utils.h"
#include "sockets.h"
#include "structs.h"

int main(int argc, char **argv)
{
	if(argc < 3) error("Uso: client hostname porta\n");
	void* buffer = (char*) malloc(DEFAULT_SIZE);
	char address_str[INET_ADDRSTRLEN];
	IPV4_Address address,client_address;
	SOCKET socket;

	socket = create_socket(IPV4,TCP,DEFAULT);
	address = ipv4_address(argv[1],atoi(argv[2]));
	client_address = ipv4_address("",atoi(argv[2]));
	bind_socket(socket,(Address*)&client_address);
	connect_socket(socket,(Address*)&address);

	forever{	
		memset(buffer,' ',DEFAULT_SIZE);
		buffer = read_input(DEFAULT_SIZE);
		get_ipv4_address(address_str);
		sprintf(buffer,"%s %s",(char*)buffer,address_str);
		write(socket,buffer,DEFAULT_SIZE);
		read(socket,buffer,DEFAULT_SIZE);
		printf("%s\n",(char*)buffer);
		if(strstr((char*)buffer,"Terminated")) break;
	}
	close(socket);
	return 0;
}
