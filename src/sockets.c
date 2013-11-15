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

void
get_ipv4_address(char* address)
{
	char addressBuffer[INET_ADDRSTRLEN];
	getifaddrs(&ifAddrStruct);
	for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa ->ifa_addr->sa_family==AF_INET) {
			tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
			inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
			strcpy(address,addressBuffer); 
		}
	}
	freeifaddrs(ifAddrStruct);
}

void
get_ipv6_address(char* address)
{
	char addressBuffer[INET6_ADDRSTRLEN];
	getifaddrs(&ifAddrStruct);
	for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr->sa_family==AF_INET6) {
			tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
			inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
			strcpy(address,addressBuffer); 
		}
	} 
	freeifaddrs(ifAddrStruct);
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
create_socket(int ip_version,int socket_type,int socket_protocol)
{
	int socket_file;
	socket_file = socket(ip_version,socket_type,0);
	if(socket_file < 0) error("ERRO ao tentar abrir o soquete");
	#ifdef WIN32
	ULONG yes = 1;
	ioctlsocket(sock, FIONBIO, &yes);
	#else
	int blocking = TRUE;
	int flags = fcntl(socket_file, F_GETFL, 0);
	if (flags < 0) error("ERRO ao desbloquear o soquete");
	flags = blocking ? (flags&~O_NONBLOCK) : (flags|O_NONBLOCK);
	fcntl(socket_file, F_SETFL, flags);
	#endif
	return socket_file;
}

struct
sockaddr_in
ipv4_address
(const char* ip_address,
 int port_number)
{
	struct sockaddr_in serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_number);
	if(strlen(ip_address) != 0) 
		inet_pton(AF_INET,ip_address,&(serv_addr.sin_addr));
	else serv_addr.sin_addr.s_addr = INADDR_ANY;
	return serv_addr;
}

struct
sockaddr_in6
ipv6_address
(const char* host_name,
 int port_number)
{
	struct sockaddr_in6 serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin6_family = AF_INET6;
	serv_addr.sin6_port = htons(port_number);
	if(strlen(host_name) != 0){
		#ifndef WIN32
		struct hostent *s = gethostbyname2(host_name,AF_INET6);
		#else
		struct hostent *s = gethostbyname(host_name);
		#endif
		if(s == NULL) error("ERRO, nenhum host encontrado\n");
		bcopy((char*)s->h_addr,(char*)&serv_addr.sin6_addr.s6_addr,s->h_length);
	}else serv_addr.sin6_addr = in6addr_any;
	return serv_addr;
}

void
connect_socket
(SOCKET socket_file,
 struct sockaddr* address)
{
	int status = -1;
	int f = socket_file;
	status = connect(f,address,socket_size(address->sa_family));
	if(status < 0) error("ERRO ao conectar");
}

void
bind_socket
(SOCKET socket_file,
 struct sockaddr* address)
{
	int sock = socket_file;
	int size = socket_size(address->sa_family);
	if(bind(sock,address,size) > 1)
		error("ERRO ao ligar o socket ao hostname");
}

int
listen_socket
(SOCKET socket_file,
 struct sockaddr* address)
{
	int newsocket;
	int socket = socket_file;
	socklen_t size = socket_size(address->sa_family);
	bind_socket(socket_file,address);
	listen(socket,5);
	newsocket = accept(socket,(struct sockaddr*)malloc(size),&size);
	if(newsocket < 0) error("ERRO ao aceitar a conexao com o cliente");
	return newsocket;
}
 
void
recv_socket
(SOCKET socket_file,
 struct sockaddr* address,
 void* buffer,
 int buffer_size)
{
	int bytes = 0;
	int socket = socket_file;
	socklen_t size = socket_size(address->sa_family);
	bytes = recvfrom(socket,buffer,buffer_size,0,address,&size);
	if(bytes == -1) error("ERRO ao receber do soquete");
}

void
send_socket
(SOCKET socket_file,
 struct sockaddr* address,
 void* buffer)
{
	int bytes = 0;
	int socket = socket_file;
	socklen_t size = socket_size(address->sa_family);
	bytes = sendto(socket,buffer,strlen(buffer),0,address,size);
	if(bytes == -1) error("ERRO ao enviar para o soquete");
}
