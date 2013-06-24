typedef struct {
	uint8_t opcode;
	int8_t padding0;
	uint16_t pkglen;
	int32_t ipdst[4];
	int32_t ipsrc[4];
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
	uint8_t filename[254];
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
	uint8_t data[2048];
} Data;

void header_packet(Header* packet);
void connection_packet(Connection* packet);
void configuration_packet(Confirmation* packet);