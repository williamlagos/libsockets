#include"compat.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  
#define bcopy(b1,b2,len) (memmove((b2), (b1), (len)), (void) 0)
#define IPV6 AF_INET6
#define IPV4 AF_INET
#define PACKET AF_PACKET
#define RAW SOCK_RAW
#define UDP SOCK_DGRAM
#define TCP SOCK_STREAM
#define DEFAULT 0
#define ETH ETH_P_ALL
#define forever while(1)
#define TRUE 1
#define FALSE 0
#define BOOL int
#define PROTO int

struct ifaddrs* ifAddrStruct;
struct ifaddrs* ifa;
void* tmpAddrPtr;

typedef struct sockaddr Address;
typedef struct sockaddr_in  IPV4_Address;
typedef struct sockaddr_in6 IPV6_Address;

int socket_size(int ip_version);
int create_socket(int ip_version,int socket_type,int socket_protocol);
int listen_socket(SOCKET socket_file,struct sockaddr* address);
void bind_socket(SOCKET socket_file,struct sockaddr* address);
void recv_socket(SOCKET socket_file,struct sockaddr* address,void* buffer,int buffer_size);
void send_socket(SOCKET socket_file,struct sockaddr* address,void* buffer);
void connect_socket(SOCKET socket_file,struct sockaddr* address);
struct sockaddr_in  ipv4_address(const char* host_name,int port_number);
struct sockaddr_in6 ipv6_address(const char* host_name,int port_number);
void get_ipv4_address(char* address);
void get_ipv6_address(char* address);
void error(const char *msg);
char* read_input(int buffer_size);

BOOL init();
void cleanup();
SOCKET connect(PROTO protocol, const char* address, uint16_t port, struct sockaddr_storage* sockaddr, socklen_t* addrlen);
SOCKET bind(PROTO protocol, const char* address, uint16_t port, struct sockaddr_storage* sockaddr, socklen_t* addrlen);