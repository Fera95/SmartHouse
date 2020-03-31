#ifndef LIB_SERVER_H
#define LIB_SERVER_H

#define SOCKET_ERROR 	1
#define BIND_ERROR 		2
#define LISTEN_ERROR 	3
#define ACCEPT_ERROR 	4
#define MAX_CLIENTS 	20
#define BUFFER_SIZE 	2048

#define TYPE_ERROR      1
#define SYMBOL_ERROR    2
#define SIZE_ERROR 		3
#define AMOUNT_ERROR    4
#define POSITION_ERROR  5

#define led_bedroom	2		// GPIO2
#define led_bathroom 3		// GPIO3
#define led_hallway	4		// GPIO4
							// GND
#define led_kitchen 17		// GPIO17
#define led_studio 27		// GPIO27
#define door_bedroom 22		// GPIO22
							// 3V3 power
#define door_bathroom 10	// GPIO10
#define door_hallway 9		// GPIO9
#define door_kitchen 11		// GPIO11
							// GND
#define door_studio 0       // GPIO0
                    		// GPIO5
							// GPIO6
							// GPIO13
							// GPIO19
							// GPIO26
							// GND

enum pinValues {HIGH = 1, LOW = 0};
enum pinState {INPUT = 1, OUTPUT = 0};

typedef struct {
	uint8_t bedroom;
	uint8_t bathroom;
	uint8_t hallway;
	uint8_t kitchen;
	uint8_t studio;
} devices_t;

typedef struct {
    int socket_descriptor;
    int port;
    struct sockaddr_in direction;
    devices_t* leds;
    devices_t* doors;
} server_t;

typedef struct {
    int socket_descriptor;
    struct sockaddr client_sockaddr;
    socklen_t length;
    char buffer[BUFFER_SIZE];
    char *ip;
} client_t;

struct sockaddr_in get_direction(server_t *server);
uint8_t bind_socket(server_t *server);
uint8_t listen_server(server_t *server);
uint8_t init_server(server_t *server, int port);
uint8_t close_server(server_t *server);

char *get_ip(client_t *client);
uint8_t accept_client(server_t *server, client_t *client);
uint8_t close_client(client_t *client);
uint8_t process_client(client_t *client, server_t* server);

void trim_query(client_t *client);
void delimit_query(client_t *client);
uint8_t set_params(const char *query, server_t *server, int function);
const char* jsonPicker (int code);
uint8_t process_query(client_t* client, server_t* server);

uint8_t send_text(client_t* client, const char* text);
uint8_t send_json(client_t* client, const char* text);
uint8_t send_error(client_t* client);

void init_devices(server_t *server);

void write_int(int data, char *write_path);
void write_char(char *data, char *write_path);

void digitalWrite (short pin, int value);
int digitalRead (short pin);

void pinMode(short pin, int mode);

#endif