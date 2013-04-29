#include"utils.h"
#include"sockets.h"

struct
sockaddr_in6
build_ipv6_address
(const char* host_name,
 int port_number)
{
	struct sockaddr_in6 serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin6_family = AF_INET6;
	serv_addr.sin6_port = htons(port_number);
	if(strlen(host_name) != 0){
		struct hostent *s = gethostbyname2(host_name,AF_INET6);
		if(s == NULL) error("ERRO, nenhum host encontrado\n");
		bcopy((char*)s->h_addr,(char*)&serv_addr.sin6_addr.s6_addr,s->h_length);
	}else serv_addr.sin6_addr = in6addr_any;
	return serv_addr;
}

void
connect_ipv6_socket
(int* socket_file,
 struct sockaddr_in6 server_addr)
{
	int fd = *socket_file;
	int status = connect(fd,(struct sockaddr*) &server_addr,
	   		 sizeof(server_addr));
	if(status < 0) error("ERRO ao conectar");
}

int
listen_ipv6_socket
(int *socket_file,
 struct sockaddr_in6 address)
{
	int socket = *socket_file;
	struct sockaddr_in6 client_address;
	if(bind(socket,(struct sockaddr*)&address,sizeof(address)) > 0)
		error("ERRO ao ligar o socket ao hostname");
	listen(socket,5);
	socklen_t client_len = sizeof(client_address);
	int newsocket = accept(socket,(struct sockaddr*)&client_address,&client_len);
	if(newsocket < 0) error("ERRO ao aceitar a conexao com o cliente");
	return newsocket;
}
