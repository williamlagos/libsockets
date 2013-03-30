#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main (int argc, char** argv)
{
	int sockfd,newsockfd,port_number,client_len,n;
	struct sockaddr_in server_addr,client_addr;
	char buffer[256];
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0){ perror("ERRO ao abrir o socket"); return 1; }
	
	port_number = 5001;
	bzero((char*) &server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port_number);

	if(bind(sockfd,(struct sockaddr*) &server_addr,
		sizeof(server_addr)) > 0){
		perror("ERRO ao ligar o socket ao hostname");
		return 1;
	}
	
	listen(sockfd,5);
	client_len = sizeof(client_addr);
	
	newsockfd = accept(sockfd,(struct sockaddr*) &client_addr, &client_len);
	
	if(newsockfd < 0){ perror("ERRO ao aceitar a conexao com o cliente"); return 1; }
	
	bzero(buffer,256);
	n = read(newsockfd,buffer,255);
	if(n < 0){ perror("ERRO ao ler do socket"); }
	printf("Aqui esta a mensagem: %s\n",buffer);

	n = write(newsockfd,"Eu consegui ler a tua mensagem",30);
	if(n < 0){ perror("ERRO ao escrever no socket"); return 1; }

	close(newsockfd);
	close(sockfd);

	return 0;
}
