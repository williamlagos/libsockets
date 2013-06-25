typedef struct {
	uint8_t opcode;
	int8_t padding0;
	uint16_t pkglen;
	IPV6_Struct ipdst;
	IPV6_Struct ipsrc;
	uint16_t srcport;
	uint16_t dstport;
	uint8_t clientid;
	uint8_t crctype;
	int16_t padding1;
	int32_t crc;
} Header;

typedef struct {
	uint8_t opcode;
	int8_t padding;
	uint16_t window;
	uint32_t filesize;
	char filename[254];
} Connection;

typedef struct {
	uint8_t opcode;
	int8_t padding[3];
	uint32_t number;
} Confirmation;

typedef struct {
	uint32_t seqnumber;
	uint16_t datalen;
	int16_t padding;
	char data[2048];
} Data;

void header_packet(Header* packet,int opcode,IPV6_Address* addr_dst,IPV6_Address* addr_src,int port_num);
void unpack_header(Header* packet,IPV6_Address* addr,int port_num);
void connection_packet(Connection* packet,int connectype,int windowsize,char* filename);
void unpack_connection(Connection* packet,IPV6_Address* addr,int port_num);
void confimation_packet(Confirmation* packet,int confirmationcode,int sequencenumber);
void unpack_confirmation(Confirmation* packet,IPV6_Address* addr,int port_num);
void data_packet(Data* packet,char* filename);
void unpack_data(Data* packet,char* filename);