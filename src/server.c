#include "utils.h"
#include "sockets.h"
#include "structs.h"

void receive_word(char* word)
{
	printf("AAAA%s",word);
}

int main(int argc, char** argv)
{
	SOCKET socket,newsocket;
	int client_count;
	void* buffer;
	Header* head;
	IPV4_Address address;
	if(argc < 2) error("Uso: server porta\n");
	socket = create_socket(IPV4,TCP,DEFAULT);
	address = ipv4_address("",atoi(argv[1]));
	bind_socket(socket,(Address*)&address);
	buffer = (void*) malloc(256);
	/*while(1){
		recv_socket(&socket,(Address*)&address,buffer,256);
		head = (Header*) buffer;
		printf("Mensagem lida: %c\n",head->opcode);
		send_socket(&socket,(Address*)&address,buffer);
	}*/
	forever{
		newsocket = listen_socket(
		socket,(struct sockaddr*)&address);
		client_count += 1;
		printf("Client %d connected",client_count);
		read(newsocket,buffer,255);
		receive_word((char*)buffer);
		write(newsocket,buffer,255);
	}
	close(newsocket);
	close(socket);
	return 0;
}
