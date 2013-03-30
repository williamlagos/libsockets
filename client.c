#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char** argv)
{
	int sockfd,port_number,n;
	struct sockaddr_in server_addr;
	struct hostent *server;

	char buffer[256];

	if(argc < 3){ fprintf(stderr,"Uso: %s hostname porta\n",argv[0]); return 0; }
	port_number = atoi(argv[2]);
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0){ perror("ERRO ao abrir socket"); return 1; }
	
	server = gethostbyname(argv[1]);
	if(server == NULL){ fprintf(stderr,"ERRO, nenhum host encontrado\n"); return 0; }
	
	bzero((char*) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	bcopy((char*) server->h_addr,
	      (char*) &server_addr.sin_addr.s_addr,
	      server->h_length);
	server_addr.sin_port = htons(port_number);
	
	if(connect(sockfd,&server_addr,sizeof(server_addr)) > 0){ perror("ERRO ao conectar"); return 1; }
	printf("Por favor, entre com a mensagem para o servidor: ");
	bzero(buffer,256);
	fgets(buffer,255,stdin);

	n = write(sockfd,buffer,strlen(buffer));
	if(n < 0){ perror("Erro ao escrever no socket"); return 1; }
	
	bzero(buffer,256);
	n = read(sockfd,buffer,255);
	if(n < 0){ perror("ERRO ao ler do socket"); return 1; }
	printf("%s\n",buffer);
	return 0;
}
