#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

void 
error
(const char *msg)
{
	perror(msg);
	exit(1);
}

int 
create_socket()
{
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd < 0) error("ERRO ao tentar abrir o soquete");
	return fd;
}

struct
sockaddr_in
build_address
(const char* host_name,
 int port_number)
{
	struct sockaddr_in serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_number);
	if(strlen(host_name) != 0){
		struct hostent *s = gethostbyname(host_name);
		if(s == NULL) error("ERRO, nenhum host encontrado\n");
		bcopy((char*)s->h_addr,(char*)&serv_addr.sin_addr.s_addr,s->h_length);
	}else serv_addr.sin_addr.s_addr = INADDR_ANY;
	return serv_addr;
}

void
connect_socket
(int* socket_file,
 struct sockaddr_in server_addr)
{
	int fd = *socket_file;
	int status = connect(fd,(struct sockaddr*) &server_addr,
	   		 sizeof(server_addr));
	if(status < 0) error("ERRO ao conectar");
}

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
