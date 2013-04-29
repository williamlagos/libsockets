#include"utils.h"
#include"sockets.h"

void 
error
(const char *msg)
{
	perror(msg);
	exit(1);
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
	if(ip_version == AF_INET) 
		return sizeof(struct sockaddr_in);
	else if(ip_version == AF_INET6) 
		return sizeof(struct sockaddr_in6);
}

int 
create_socket(int ip_version,int socket_type)
{
	int socket_file;
	socket_file = socket(ip_version,socket_type,0);
	if(socket_file < 0) error("ERRO ao tentar abrir o soquete");
	return socket_file;
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
		struct hostent *s = gethostbyname2(host_name,AF_INET);
		if(s == NULL) error("ERRO, nenhum host encontrado\n");
		bcopy((char*)s->h_addr,(char*)&serv_addr.sin_addr.s_addr,s->h_length);
	}else serv_addr.sin_addr.s_addr = INADDR_ANY;
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
	if(status < 0) error("ERRO ao conectar");
}

void
bind_socket
(int* socket_file,
 struct sockaddr* address)
{
	int socket = *socket_file;
	int size = socket_size(address->sa_family);
	if(bind(socket,address,size) > 1)
		error("ERRO ao ligar o socket ao hostname");
}

int
listen_socket
(int* socket_file,
 struct sockaddr* address)
{
	int socket = *socket_file;
	int size = socket_size(address->sa_family);
	bind_socket(socket_file,address);
	listen(socket,5);
	int newsocket = accept(socket,(struct sockaddr*)malloc(size),&size);
	if(newsocket < 0) error("ERRO ao aceitar a conexao com o cliente");
	return newsocket;
}
 
void
recv_socket
(int* socket_file,
 struct sockaddr* address,
 char* buffer)
{
	int bytes = 0;
	int socket = *socket_file;
	int size = socket_size(address->sa_family);
	bytes = recvfrom(socket,buffer,strlen(buffer),0,address,&size);
	if(bytes == -1) error("ERRO ao receber do soquete");
	buffer[bytes] = '\0';
}

void
send_socket
(int* socket_file,
 struct sockaddr* address,
 char* buffer)
{
	int bytes = 0;
	int socket = *socket_file;
	int size = socket_size(address->sa_family);
	bytes = sendto(socket,buffer,strlen(buffer),0,address,size);
	if(bytes == -1) error("ERRO ao enviar para o soquete");
	buffer[bytes] = '\0';
}
