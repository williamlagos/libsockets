#include<unistd.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#define IPV6_ENABLED 6
#define IPV6_DISABLED 4

int create_socket(int ipversion);
int listen_socket(int *socket_file,struct sockaddr_in address);
int listen_ipv6_socket(int *socket_file,struct sockaddr_in6 address);
void connect_socket(int* socket_file,struct sockaddr_in server_addr);
void connect_ipv6_socket(int* socket_file,struct sockaddr_in6 server_addr);
struct sockaddr_in build_address(const char* host_name,int port_number);
struct sockaddr_in6 build_ipv6_address(const char* host_name,int port_number);
