#include"utils.h"
#include"sockets.h"

void
logto
(const char *type,
 const char *msg)
{
	printf("[%s] %s\n",type,msg);
	FILE* file = fopen("sockets.log","a+");
	fprintf(file,"[%s] %s\n",type,msg);
	fclose(file);
}

void 
error
(const char *msg,
 int exitcode)
{
	logto("ERRO",msg);
	perror(msg);
	exit(exitcode);
}

char*
read_input
(int buffer_size)
{
	char* buffer = (char*) malloc(buffer_size);
	puts("Por favor, entre com a mensagem: ");
	bzero(buffer,buffer_size-1);
	fgets(buffer,buffer_size-1,stdin);
	return buffer;
}

int
socket_size
(int ip_version)
{
	if(ip_version == AF_INET6) 
		return sizeof(struct sockaddr_in6);
	return sizeof(struct sockaddr_in);
}

int 
create_socket(int ip_version,int socket_type)
{
	int socket_file;
	socket_file = socket(ip_version,socket_type,0);
	if(socket_file < 0) error("ERRO ao tentar abrir o soquete",1);
	return socket_file;
}

struct
sockaddr_in
ipv4_address
(const char* address,
 int port_number)
{
	struct sockaddr_in serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_number);
	inet_pton(serv_addr.sin_family,address,&(serv_addr.sin_addr));
	return serv_addr;
}

struct
sockaddr_in6
ipv6_address
(const char* address,
 int port_number)
{
	struct sockaddr_in6 serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin6_family = AF_INET6;
	serv_addr.sin6_port = htons(port_number);
	inet_pton(serv_addr.sin6_family,address,&(serv_addr.sin6_addr));
	return serv_addr;
}

void
connect_socket
(int* socket_file,
 struct sockaddr* address)
{
	int status = -1;
	int f = *socket_file;
	status = connect(f,address,socket_size(address->sa_family));
	if(status < 0) error("ERRO ao conectar",1);
}

void
bind_socket
(int* socket_file,
 struct sockaddr* address)
{
	int socket = *socket_file;
	int size = socket_size(address->sa_family);
	if(bind(socket,address,size) > 1)
		error("ERRO ao ligar o socket ao hostname",1);
}

int
listen_socket
(int* socket_file,
 struct sockaddr* address)
{
	int socket = *socket_file;
	socklen_t size = socket_size(address->sa_family);
	bind_socket(socket_file,address);
	listen(socket,5);
	int newsocket = accept(socket,(struct sockaddr*)malloc(size),&size);
	if(newsocket < 0) error("ERRO ao aceitar a conexao com o cliente",1);
	return newsocket;
}
 
void
recv_socket
(int* socket_file,
 struct sockaddr* address,
 void* buffer,
 int buffer_size)
{
	int bytes = 0;
	int socket = *socket_file;
	socklen_t size = socket_size(address->sa_family);
	bytes = recvfrom(socket,buffer,buffer_size,0,address,&size);
	if(bytes == -1) error("ERRO ao receber do soquete",1);
}

void
send_socket
(int* socket_file,
 struct sockaddr* address,
 void* buffer,
 int buffer_size)
{
	int bytes = 0;
	int socket = *socket_file;
	socklen_t size = socket_size(address->sa_family);
	bytes = sendto(socket,buffer,buffer_size,0,address,size);
	if(bytes == -1) error("ERRO ao enviar para o soquete",1);
}

struct 
sockaddr_in6
ipv6_ifaddress
(const char* interface,
 int port_number)
{
	struct ifaddrs* ifa;
	struct sockaddr_in6* addr;
	getifaddrs(&ifa);
	while (ifa != NULL) {
		if(ifa->ifa_addr->sa_family == AF_INET6 && 
		   strcmp(interface,ifa->ifa_name) == 0)
			addr = (struct sockaddr_in6*) ifa->ifa_addr;
			addr->sin6_port = htons(port_number);
		ifa = ifa->ifa_next;
	}
	return *addr;
}