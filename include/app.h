#define MESSAGE_SIZE 32

typedef struct {
	char address[16];
	char command[16];
	char results[32];
	char options[32];
} DATA;

typedef struct {
	int id;
	char address[16];
} PLAYER;

#define DEFAULT_SIZE sizeof(DATA)
#define DEFAULT_PORT 5001
DATA* buffer;
