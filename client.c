#include "sockets.h"

int 
create_socket()
{
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd < 0) error("ERRO ao tentar abrir o soquete");
	else return fd;
}

struct
sockaddr_in
build_address
(const char* host_name,
 int port_number)
{
	struct sockaddr_in serv_addr;
	struct hostent *server = gethostbyname(host_name);
	if(server == NULL) error("ERRO, nenhum host encontrado\n");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
		(char *)&serv_addr.sin_addr.s_addr,
		server->h_length);
	serv_addr.sin_port = htons(port_number);
	return serv_addr;
}

void
connect_socket
(int* socket_file,
 struct sockaddr_in server_addr)
{
	int status,fd;
	fd = *socket_file;
	status = connect(fd,(struct sockaddr*) &server_addr,
	   		 sizeof(server_addr));
	if(status < 0) error("ERRO ao conectar");
}

void
writeto_socket
(int *socket_file, int size)
{
	int fd = *socket_file;
	char buffer[size];
	puts("Por favor, entre com a mensagem para o servidor: ");
	bzero(buffer,size-1);
	fgets(buffer,size-1,stdin);
	int n = write(fd,buffer,strlen(buffer));
	if(n < 0) error("Erro ao escrever no socket");
}
	
void
readfrom_socket
(int *socket_file, int size)
{
	int status,fd;
	fd = *socket_file;
	char buffer[size];
	bzero(buffer,size-1);
	status = read(fd,buffer,strlen(buffer));
	if(status < 0) error("ERRO ao ler do socket");
	else printf("%s\n",buffer);
}

int 
main(int argc, char** argv)
{
	if(argc < 3) error("Uso: client hostname porta\n");
	int socket_file = create_socket(&socket_file);
	struct sockaddr_in address = 
	build_address(argv[1],atoi(argv[2]));
	connect_socket(&socket_file,address);
	writeto_socket(&socket_file,256);
	readfrom_socket(&socket_file,256);
	return 0;
}
