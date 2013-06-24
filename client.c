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
	Connection* conn = (Connection*) malloc(sizeof(Connection));
	Confirmation* conf = (Confirmation*) malloc(sizeof(Confirmation));
	header_packet(head,&address,&client_address,port_num);
	connection_packet(conn,ESTABLISH,31,"teste.txt");
	send_socket(&socket,(Address*)&address,(Header*)head,sizeof(Header)*8);
	send_socket(&socket,(Address*)&address,(Connection*)conn,sizeof(Connection)*8);	
	recv_socket(&socket,(Address*)&address,(Confirmation*)conf,sizeof(Confirmation)*8);
	if(conf->opcode == 1) logto("DONE","Pronto para enviar arquivos");
	close(socket);
	return 0;
}
