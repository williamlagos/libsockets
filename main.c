#include "sockets.h"

int
listen_socket
(int *socket_file,
 struct sockaddr_in address)
{
	int socket = *socket_file;
	struct sockaddr_in client_address;
	if(bind(socket,(struct sockaddr*)&address,sizeof(address)) > 0)
		error("ERRO ao ligar o socket ao hostname");
	listen(socket,5);
	socklen_t client_len = sizeof(client_address);
	int newsocket = accept(socket,(struct sockaddr*)&client_address,&client_len);
	if(newsocket < 0) error("ERRO ao aceitar a conexao com o cliente");
	return newsocket;
} 

int main (int argc, char** argv)
{
	if(argc < 2) error("Uso: server porta\n");
	int socket = create_socket();
	struct sockaddr_in server_address = 
	build_address("",atoi(argv[1]));
	int newsocket = listen_socket(&socket,server_address);
	readfrom_socket(&newsocket,255);
	writeto_socket(&newsocket,"Eu consegui ler a tua mensagem");
	close(newsocket);
	close(socket);
	return 0;
}
