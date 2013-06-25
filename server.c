#include "utils.h"
#include "sockets.h"
#include "structs.h"

int main(int argc, char** argv)
{
	IPV6_Address address;
	void* buffer = (void*) malloc(256);
	if(argc < 2) error("Uso: server porta [interface]\n",1);
	else if(argc > 2) address = ipv6_ifaddress(argv[2],atoi(argv[1]));
	else address = ipv6_address("",atoi(argv[1]));
	int socket = create_socket(IPV6,UDP);
	bind_socket(&socket,(Address*)&address);
	forever{
		recv_socket(&socket,(Address*)&address,buffer,sizeof(Header)*8);
		// Pacote de Cabecalho
		Header* head = (Header*) buffer;
		unpack_header(head,&address,atoi(argv[1]));
		if(head->opcode == 1){
			// Pacote de Conexao
			recv_socket(&socket,(Address*)&address,buffer,sizeof(Connection)*8);
			Connection* conn = (Connection*) buffer;
			unpack_connection(conn,&address,atoi(argv[1]));
			// Pacote de Confirmacao
			Confirmation* conf = (Confirmation*) buffer;
			confirmation_packet(conf,ESTABLISHED,0);
			send_socket(&socket,(Address*)&address,buffer,sizeof(Confirmation)*8);
		}else if(head->opcode == 4){
			// Pacote de Dados
			recv_socket(&socket,(Address*)&address,buffer,sizeof(Data));
			Data* data = (Data*) buffer;
			unpack_data(data,"saida.txt");
		}
		//send_socket(&socket,(Address*)&address,buffer,256);
	}
	/*int newsocket = listen_socket(
	&socket,(struct sockaddr*)&address);
	read(newsocket,buffer,255);
	write(newsocket,buffer,255);
	close(newsocket);*/
	close(socket);
	return 0;
}
