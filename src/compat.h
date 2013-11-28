#ifndef NETWORKING_H
#define NETWORKING_H

#ifndef _WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#define SPRINTF sprintf
#define ULONG unsigned long
#define FIONBIO O_NONBLOCK
#else
#ifndef _DEBUG
#ifndef _HAS_ITERATOR_DEBUGGING
#define _HAS_ITERATOR_DEBUGGING 0
#endif
#ifndef _SECURE_SCL
#define _SECURE_SCL 0
#endif
#endif
typedef int socklen_t;
#define SPRINTF sprintf_s
#define close closesocket
#define uint16_t unsigned short
#define ssize_t unsigned int
#define uint32_t unsigned int
#define snprintf _snprintf_s
#include <ws2tcpip.h>
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")
#define OLD_WIN32_WINNT _WIN32_WINNT
#if (_WIN32_WINNT < 0x0501)
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x501
#endif
#if (_WIN32_WINNT != OLD_WIN32_WINNT)
#undef _WIN32_WINNT
#define _WIN32_WINNT OLD_WIN32_WINNT
#endif
#endif

#include <stdio.h>
#include <stdint.h>
#include <string.h>

namespace networking{
	enum TransportProtocol{
		UDP = IPPROTO_UDP, /**< UDP protocol. */
		TCP = IPPROTO_TCP /**< TCP protocol. */
	};
	bool init();
	void cleanup();
	int connect(enum TransportProtocol protocol, const char* address, uint16_t port, struct sockaddr_storage* sockaddr, socklen_t* addrlen);
	int bind(enum TransportProtocol protocol, const char* address, uint16_t port, struct sockaddr_storage* sockaddr, socklen_t* addrlen);
}
#endif

