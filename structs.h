typedef struct {
	char opcode;
	char padding0;
	short pkglen;
	char ipdst[16];
	char ipsrc[16];
	short srcport;
	short dstport;
	char clientid;
	char crctype;
	short padding1;
	int crc;
} Header;

typedef struct {
	char opcode;
	char padding;
	short window;
	int filesize;
	char filename[254];
} Connection;

typedef struct {
	char opcode;
	char padding[3];
	unsigned int number;
} Confirmation;

Header*		head_deserialize(const char* serial);
Connection*	conn_deserialize(const char* serial);
Confirmation*	conf_deserialize(const char* serial);

char* head_serialize(Header* serial);
char* conn_serialize(Connection* serial);
char* conf_serialize(Confirmation* serial);
