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
readfrom_socket
(int *socket_file, int size)
{
	int fd = *socket_file;
	char buffer[size];
	bzero(buffer,size-1);
	int status = read(fd,buffer,strlen(buffer));
	if(status < 0) error("ERRO ao ler do socket");
	else printf("%s\n",buffer);
}

void
writeto_socket
(int *socket_file, 
 const char *buffer)
{
	int fd = *socket_file;
	int n = write(fd,buffer,strlen(buffer));
	if(n < 0) error("ERRO ao escrever no socket");
}	
