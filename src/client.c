#include "app.h"
#include "sockets.h"

SOCKET man_socket;

int main(int argc, char **argv)
{
	if(argc < 3) error("Uso: client hostname porta\n");
	buffer = (DATA*) malloc(DEFAULT_SIZE);
	char* buffers_str = (char*) malloc(MESSAGE_SIZE);
	char address_str[INET_ADDRSTRLEN];
	IPV4_Address address,client_address;
	SOCKET socket;

	socket = create_socket(IPV4,TCP,DEFAULT);
	address = ipv4_address(argv[1],atoi(argv[2]));
	client_address = ipv4_address("",atoi(argv[2]));
	bind_socket(socket,(Address*)&client_address);
	connect_socket(socket,(Address*)&address);

	forever{	
		//memset(buffer,' ',DEFAULT_SIZE);
		buffers_str = read_input(MESSAGE_SIZE);
		if(strstr(buffers_str,"exit")) break;
		get_ipv4_address(address_str);
		strcpy(buffer->command,buffers_str);
		strcpy(buffer->address,address_str);
		strcpy(buffer->options," ");
		strcpy(buffer->results," ");
		write(socket,buffer,DEFAULT_SIZE);
		read(socket,buffer,DEFAULT_SIZE);
		printf("%s\n",buffer->results);
		if(strstr((char*)buffer,"Terminated")) break;
	}
	close(socket);
	return 0;
}
