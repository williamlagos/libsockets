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
