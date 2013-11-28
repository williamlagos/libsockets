#include "sockets.h"
	
BOOL 
init()
{
	BOOL ret = FALSE;
	#ifdef _WIN32
	ret = (WSAStartup(MAKEWORD(2, 0), &wsaData) == 0);
	#else
	ret = TRUE;
	#endif
	return ret;
}

void 
cleanup()
{
	#ifdef _WIN32
	WSACleanup();
	#endif
}

int 
connect
(PROTO protocol,
 const char* address,
 uint16_t port,
 struct sockaddr_storage* sockaddr,
 socklen_t* addrlen)
{
	struct addrinfo hints;
	struct addrinfo* res = NULL;
	struct addrinfo* p = NULL;
	char service[8];
	int sock = -1;
	if(!port || address == "") return -1;

	snprintf(service, sizeof(service), "%u", port);
	service[sizeof(service)-1] = 0x00;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = protocol == UDP ? SOCK_DGRAM : SOCK_STREAM;
	hints.ai_protocol = protocol;
	hints.ai_flags = 0;

	if(getaddrinfo(address, service, &hints, &res) != 0) return -1;

	for(p = res ; p ; p = p->ai_next){
		sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if(sock == -1) continue;
		if(protocol == TCP && connect(sock,(struct sockaddr*)p->ai_addr, p->ai_addrlen) == -1){
			close(sock);
			sock = -1;
			continue;
		}

		if(sockaddr) memcpy(sockaddr, p->ai_addr, p->ai_addrlen);
		if(addrlen) *addrlen = p->ai_addrlen;
		break;
	}

	freeaddrinfo(res);
	p = NULL;
	return sock;
}

int 
bind
(PROTO protocol, 
 const char* address, 
 uint16_t port, 
 struct sockaddr_storage* sockaddr, 
 socklen_t* addrlen)
{
	struct addrinfo hints;
	struct addrinfo* res = NULL;
	struct addrinfo* p = NULL;
	char service[8];
	int sock = -1;

	if(!port || address == "") return -1;

	snprintf(service, sizeof(service), "%u", port);
	service[sizeof(service)-1] = 0x00;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = protocol == UDP ? SOCK_DGRAM : SOCK_STREAM;
	hints.ai_protocol = protocol;
	hints.ai_flags = AI_PASSIVE;

	if(getaddrinfo(address,service,&hints,&res) != 0) return -1;

	for(p = res ; p ; p = p->ai_next){
		int on = 1;
		sock = socket(p->ai_family,p->ai_socktype,p->ai_protocol);
		#ifdef WIN32
		ULONG yes = 1;
		ioctlsocket(sock, FIONBIO, &yes);
		#else
		bool blocking = true;
		int flags = fcntl(sock, F_GETFL, 0);
		if (flags < 0) return false;
		flags = blocking ? (flags&~O_NONBLOCK) : (flags|O_NONBLOCK);
		return (fcntl(sock, F_SETFL, flags) == 0) ? true : false;
		#endif
		if(sock == -1) continue;

		#ifndef _WIN32
		setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));
		on = 1;
		setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, &on, sizeof(on));
		#else
		on = 0;
		#endif

		if(::bind(sock,p->ai_addr,p->ai_addrlen) == -1){
			::close(sock);
			sock = -1;
			continue;
		}

		if(sockaddr) memcpy(sockaddr, p->ai_addr, p->ai_addrlen);
		if(addrlen) *addrlen = p->ai_addrlen;
		break;
	}

	freeaddrinfo(res);
	p = NULL;

	return sock;
}