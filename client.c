#include "utils.h"
#include "sockets.h"
#include "structs.h"

int main(int argc, char **argv)
{
	char address_str[32];
	IPV6_Address client_address;
	if(argc < 3) error("Uso: client endereco porta [interface]\n",1);
	else if(argc > 3){
		sprintf(address_str,"%s%%%s",argv[1],argv[3]);
		client_address = ipv6_ifaddress(argv[3],atoi(argv[2]));
	}else{
		strcpy(address_str,argv[1]);
		client_address = ipv6_address("::1",atoi(argv[2]));
	}
	int socket = create_socket(IPV6,UDP);
	int port_num = atoi(argv[2]);
	IPV6_Address address = ipv6_address(address_str,port_num);
	bind_socket(&socket,(Address*)&client_address);
	
	/*char* buffer = read_input(256);
	send_socket(&socket,(Address*)&address,buffer);
	recv_socket(&socket,(Address*)&address,buffer,256);
	printf("Recebido:%s",buffer);*/
	
	/*connect_socket(&socket,(Address*)&address);
	write(socket,buffer,255);
	read(socket,buffer,255);*/

	Header* head = (Header*) malloc(sizeof(Header));
	header_packet(head,&address,&client_address,port_num);
	send_socket(&socket,(Address*)&address,(Header*)head,256);
	recv_socket(&socket,(Address*)&address,(Header*)head,256);
	printf("Recebido: %d\n",head->opcode);
	close(socket);
	return 0;
}
