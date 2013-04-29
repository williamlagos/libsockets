#include<unistd.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#define IPV6 AF_INET6
#define IPV4 AF_INET
#define UDP SOCK_DGRAM
#define TCP SOCK_STREAM

int socket_size(int ip_version);
int create_socket(int ip_version,int socket_type);
int listen_socket(int* socket_file,struct sockaddr* address);
int listen_ipv6_socket(int* socket_file,struct sockaddr_in6 address);
void recv_socket(int* socket_file,struct sockaddr* address,char* buffer);
void recv_ipv6_socket(int* socket_file,struct sockaddr_in6 address,char* buffer);
void connect_socket(int* socket_file,struct sockaddr* address);
void connect_ipv6_socket(int* socket_file,struct sockaddr_in6 server_addr);
struct sockaddr_in build_address(const char* host_name,int port_number);
struct sockaddr_in6 build_ipv6_address(const char* host_name,int port_number);
