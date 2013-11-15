#ifndef WIN32
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<fcntl.h>
#include<ifaddrs.h>
#include<arpa/inet.h>
#define ULONG unsigned long
#define FIONBIO O_NONBLOCK
#define SOCKET int
#else
#include<io.h>
#include<ws2tcpip.h>
#include<winsock2.h>
#include<windows.h>
#pragma comment(lib, "ws2_32.lib")
#endif
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
