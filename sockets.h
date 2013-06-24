#include<unistd.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<ifaddrs.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>

#define IPV6 AF_INET6
#define IPV4 AF_INET
#define UDP SOCK_DGRAM
#define TCP SOCK_STREAM

typedef struct sockaddr Address;
typedef struct sockaddr_in6 IPV6_Address;
typedef struct in6_addr IPV6_Struct;

int socket_size(int ip_version);
int create_socket(int ip_version,int socket_type);
int listen_socket(int* socket_file,struct sockaddr* address);
void bind_socket(int* socket_file,struct sockaddr* address);
void recv_socket(int* socket_file,struct sockaddr* address,void* buffer,int buffer_size);
void send_socket(int* socket_file,struct sockaddr* address,void* buffer,int buffer_size);
void connect_socket(int* socket_file,struct sockaddr* address);
struct sockaddr_in  ipv4_address(const char* address,int port_number);
struct sockaddr_in6 ipv6_address(const char* address,int port_number);
struct sockaddr_in6 ipv6_ifaddress(const char* interface,int port_number);
