#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/ioctl.h>          
#include <sys/types.h>         
#include <sys/socket.h>        
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <net/if.h> 	
#include <arpa/inet.h>
#include <net/ethernet.h>       
#include <linux/if_packet.h>

#define IPV4_TYPE 0x0800

unsigned char buff[1500];

struct Ethernet
{
	unsigned char cmd;
        char txt[1400];
	// int address;
	// unsigned char mac[6];
};

void 
ethernet_packet()
{
	struct ether_header *eth;
	eth = (struct ether_header *) &buff[0];
	//Destination MAC Address
	eth->ether_dhost[0] = 0XFF; 
	eth->ether_dhost[1] = 0XFF;
	eth->ether_dhost[2] = 0XFF;
	eth->ether_dhost[3] = 0XFF;
	eth->ether_dhost[4] = 0XFF;
	eth->ether_dhost[5] = 0XFF;
	//Source MAC Address
	eth->ether_shost[0] = 0X00;
	eth->ether_shost[1] = 0X15;
	eth->ether_shost[2] = 0Xc5;
	eth->ether_shost[3] = 0X33;
	eth->ether_shost[4] = 0X87;
	eth->ether_shost[5] = 0Xf5;
	eth->ether_type = htons(IPV4_TYPE);
}

void 
raw_header()
{
	struct Ethernet *data;
        data = (struct Data *) &buff[14];
        data->cmd = '1'; //Defines the option protocol
        strcpy(data->txt, "teste final");
	printf("TAM: %d\n", strlen(data->txt));
	if(strlen(data->txt)<1399) strcat(data->txt,"\0");
}

unsigned short 
create_checksum
(unsigned short *addr,
 int len)
{
        register int sum = 0;
        u_short answer = 0;
        register u_short *w = addr;
        register int nleft = len;
        while (nleft > 1){
		sum += *w++;
                nleft -= 2;
        }
        if (nleft == 1) {
                *(u_char *)(&answer) = *(u_char *)w;
                sum += answer;
        }
        sum = (sum >> 16) + (sum & 0xffff);
        sum += (sum >> 16);
        answer = ~sum;
        return(answer);
}

void 
ipv4_header
(char *iporig,
 char *ipdest,
 int df)
{
	struct iphdr *ipheader = (struct iphdr *) &buff[14];
	bzero((char *)ipheader,sizeof(struct iphdr));
	ipheader->ihl = 5;
	ipheader->version = 4;
	ipheader->protocol = 0x01; // pacote ICMP
	#ifdef IP_LEN_HORDER
	ipheader->tot_len = (sizeof(buff));
	#else
	ipheader->tot_len = htons(sizeof(buff));
	#endif
	ipheader->saddr = inet_addr(ip_origem);
	ipheader->daddr = inet_addr(ip_destino);
	ipheader->check = in_cksum((unsigned short *)ipheader,sizeof(struct iphdr));
}

void
icmpv4_header
(int icmp_type,
 int icmp_code,
 int icmp_csum)
{
	struct icmphdr *icmpheader = (struct icmphdr *)(buff+sizeof(struct iphdr));
	bzero((char *)icmpheader,sizeof(struct icmphdr));
	icmpheader->type = icmp_type;
	icmpheader->code = icmp_code;
	icmpheader->checksum = icmp_csum;
}

void
ipv6_header()
{

}

void
icmpv6_header()
{

}

void
promiscuous_mode()
{
	strcpy(ifr.ifr_name, "eth0");
	if (ioctl(sock, SIOCGIFINDEX, &ifr) <0)
		printf("erro no ioctl");
}

/*int main(int argc,char *argv[])
{
	int sock, i;
	struct ifreq ifr;
	struct sockaddr_ll to;
	socklen_t len;
	unsigned char addr[6];

        memset(&ifr, 0, sizeof(ifr));

	if((sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0)  {
		perror("Erro na criacao do socket");
    		exit(0);
 	}

	
	to.sll_protocol= htons(ETH_P_ALL);
	to.sll_ifindex = ifr.ifr_ifindex;
	to.sll_halen = ETH_ALEN;
	monta_pacote();
	monta_pacote_ipv4("10.32.143.201","10.32.143.255",0);
	monta_pacote_icmpv4();
	//adiciona_dados_op1();

	memcpy (to.sll_addr, buff, 6);
	len = sizeof(struct sockaddr_ll);
	
	if(sendto(sock, (char *) buff, sizeof(buff), 0, (struct sockaddr*) &to, len)<0)
			perror("sendto maquina B");

	printf("Pacote enviado para maquina B\n");
}*/
