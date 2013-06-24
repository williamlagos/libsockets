typedef struct {
	unsigned char opcode;
	char padding0;
	unsigned char pkglen[2];
	char ipdst[16];
	char ipsrc[16];
	unsigned char srcport[2];
	unsigned char dstport[2];
	char clientid;
	char crctype;
	char padding1[2];
	char crc[4];
} Header;

typedef struct {
	char opcode;
	char padding;
	char window[2];
	char filesize[2];
	char filename[254];
} Connection;

typedef struct {
	char opcode;
	char padding[3];
	unsigned char number[4];
} Confirmation;

void header_packet(Header* packet);
void connection_packet(Connection* packet);
void configuration_packet(Confirmation* packet);