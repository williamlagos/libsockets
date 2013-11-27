#include"app.h"
#include"sockets.h"

int clients_count;
char complete_word[64];
SOCKET man_socket;
SOCKET invite_socket;
BOOL is_terminated;
PLAYER players[4];

void enter_onserver(char* address)
{
	char message[MESSAGE_SIZE];
	PLAYER player;
	clients_count += 1;
	player.id = clients_count;
	strcpy(player.address,address);
	players[clients_count] = player;
	sprintf(message,"P%d connected, %s",clients_count,address);
	strcpy(buffer->results,message);
	write(man_socket,buffer,DEFAULT_SIZE);
}

void invite_player(char* cmd)
{
	int number;
	IPV4_Address address,client_address;
	char* number_str = malloc(sizeof(int));
	char message[MESSAGE_SIZE];
	number_str = strtok(cmd," ");
	number_str = strtok(NULL," ");
	number = atoi(number_str);
	invite_socket = create_socket(IPV4,TCP,DEFAULT);
	address = ipv4_address(players[number].address,DEFAULT_PORT);
	client_address = ipv4_address("",DEFAULT_PORT);
	bind_socket(invite_socket,(Address*)&client_address);
	connect_socket(invite_socket,(Address*)&address);
	sprintf(message,"P%d invited you",clients_count);
	strcpy(buffer->results,message);
	write(invite_socket,buffer,DEFAULT_SIZE);
	read(invite_socket,buffer,DEFAULT_SIZE);
	if(strstr(buffer->results,"yes") != NULL) puts("Started the game");
	else if(strstr(buffer->results,"no") != NULL) puts("Refused the invite");
	
}

void receive_word(char* word)
{
	int tries = 0;
	int count = 0;
	char which_word[64];
	strcpy(complete_word,word);
	strcpy(buffer->results,"Sended the word");
	write(man_socket,buffer,DEFAULT_SIZE);
	while(strlen(word) > 0){
		strcat(which_word,"_");
		count += 1;
	}
	strcpy(buffer->results,which_word);
	count = strlen(word);
	while(count > 0){
		if(tries >= 5) break;
		write(invite_socket,buffer,DEFAULT_SIZE);
		read(invite_socket,buffer,DEFAULT_SIZE);
		if(strstr(word,buffer->results) != NULL){ 
			count -= 1;
		}else tries += 1;	
	}
	if(count > 0) strcpy(buffer->results,"Ended the game");
	else strcpy(buffer->results,"Won the game");
	write(invite_socket,buffer,DEFAULT_SIZE);
	write(man_socket,buffer,DEFAULT_SIZE);
}

void read_command(char* cmd, char* addr)
{
	if(strstr(cmd,"terminate") != NULL) is_terminated = TRUE;
	else if(strstr(cmd,"enter") != NULL) enter_onserver(addr);
	else if(strstr(cmd,"invite") != NULL) invite_player(cmd);
	else if(strstr(cmd,"word") != NULL) receive_word(cmd);
	else{
		strcpy(buffer->results,"Invalid command");
		write(man_socket,buffer,DEFAULT_SIZE);
	}
}

int main(int argc, char** argv)
{
	if(argc < 2) error("Uso: server porta\n");
	buffer = (DATA*) malloc(DEFAULT_SIZE);
	char command_str[16];
	char address_str[16];
	IPV4_Address address;
	SOCKET socket;

	socket = create_socket(IPV4,TCP,DEFAULT);
	address = ipv4_address("",atoi(argv[1]));
	bind_socket(socket,(Address*)&address);
	man_socket = listen_socket(
	socket,(struct sockaddr*)&address);

	is_terminated = FALSE;
	puts("Waiting for players...");
	forever{
		//memset(buffer,' ',DEFAULT_SIZE);
		read(man_socket,buffer,DEFAULT_SIZE);
		strcpy(command_str,buffer->command);
		strcpy(address_str,buffer->address);
		printf("command: %s",command_str);
		read_command(command_str,address_str);	
		if(is_terminated == TRUE) break;
	}
	
	strcpy(buffer->results,"Terminated");
	write(man_socket,buffer,DEFAULT_SIZE);
	close(man_socket);
	close(socket);

	return 0;
}
