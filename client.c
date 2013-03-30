#include "sockets.h"

void 
create_socket
(int* socket_file)
{
	int fd = *socket_file;
	fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd < 0) error("ERRO ao tentar abrir o soquete");
	else socket_file = (int*) fd;
}

void 
build_address
(struct sockaddr_in* server_addr,
 struct hostent* server,
 int port_number)
{
	bzero((char*) server_addr, sizeof(*server_addr));
	server_addr->sin_family = AF_INET;
	bcopy((char*) server->h_addr,
	      (char*) server_addr->sin_addr.s_addr,
	      server->h_length);
	server_addr->sin_port = htons(port_number);
}

void
connect_socket
(int* socket_file,
 struct sockaddr_in* server_addr)
{
	int status,fd;
	fd = *socket_file;
	status = connect(fd,(struct sockaddr*) server_addr,
	   		 sizeof(server_addr));
	if(status < 0) error("ERRO ao conectar");
}

void
writeto_socket
(int *socket_file, int size)
{
	int fd = *socket_file;
	char buffer[size];
	printf("Por favor, entre com a mensagem para o servidor: ");
	bzero(buffer,size-1);
	fgets(buffer,size-1,stdin);
	int n = write(fd,buffer,strlen(buffer));
	if(n < 0) error("Erro ao escrever no socket");
}

int 
main(int argc, char** argv)
{
	if(argc < 3) error("Uso: client hostname porta\n");
	struct hostent *srv = gethostbyname(argv[1]);
	struct sockaddr_in socket_addr;
	int pnu = atoi(argv[2]);
	int socket_file;
	if(srv == NULL) error("ERRO, nenhum host encontrado\n");
	
	create_socket(&socket_file);
	build_address(&socket_addr,srv,pnu);
	connect_socket(&socket_file,&socket_addr);
	writeto_socket(&socket_file,256);
	return 0;
	
	/*bzero(buffer,256);
	n = read(sockfd,buffer,255);
	if(n < 0) error("ERRO ao ler do socket");
	printf("%s\n",buffer);
	return 0;*/
}
