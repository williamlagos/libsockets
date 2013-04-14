#include<unistd.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

int create_socket();
int listen_socket(int *socket_file,struct sockaddr_in address);
void connect_socket(int* socket_file,struct sockaddr_in server_addr);
struct sockaddr_in build_address(const char* host_name,int port_number);
