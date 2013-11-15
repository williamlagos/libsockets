#include"server.h"

void enter_onserver()
{
	clients_count += 1;
	sprintf(buffer,"Client %d connected",clients_count);
	write(man_socket,buffer,DEFAULT_SIZE);
}

void read_command(char* cmd)
{
	if(strstr(cmd,"terminate") != NULL) is_terminated = TRUE;
	else if(strstr(cmd,"enter") != NULL) enter_onserver();
	else write(man_socket,"Invalid command",DEFAULT_SIZE);
}

void receive_word(char* word)
{
	printf("AAAA%s",word);
}

int main(int argc, char** argv)
{
	if(argc < 2) error("Uso: server porta\n");
	buffer = (char*) malloc(DEFAULT_SIZE);
	IPV4_Address address;
	SOCKET socket;

	socket = create_socket(IPV4,TCP,DEFAULT);
	address = ipv4_address("",atoi(argv[1]));
	bind_socket(socket,(Address*)&address);
	man_socket = listen_socket(
	socket,(struct sockaddr*)&address);

	is_terminated = FALSE;
	forever{
		memset(buffer,' ',DEFAULT_SIZE);
		puts("Server restart");
		read(man_socket,buffer,DEFAULT_SIZE);
		read_command((char*)buffer);	
		if(is_terminated == TRUE) break;
	}
	
	write(man_socket,"Terminated",DEFAULT_SIZE);
	close(man_socket);
	close(socket);

	return 0;
}
