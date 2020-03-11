#ifndef LIB_SERVER_H
#define LIB_SERVER_H

#include <stdint.h>
#include <libarduinocomms.h>

#define SOCKET_ERROR 	1
#define BIND_ERROR 		2
#define LISTEN_ERROR 	3
#define ACCEPT_ERROR 	4
#define MAX_CLIENTS 	20
#define BUFFER_SIZE 	2048

#define TYPE_USERXPC 	0
#define TYPE_USERXUSER 	1

#define SYMBOL_0	 	0
#define SYMBOL_1 		1
#define SYMBOL_2 		2

#define SIZE_FULL		0
#define SIZE_HALF 		1
#define SIZE_QUARTER 	2

#define TYPE_ERROR      1
#define SYMBOL_ERROR    2
#define SIZE_ERROR 		3
#define AMOUNT_ERROR    4
#define POSITION_ERROR  5

#define TURN_PLAYER0    0
#define TURN_PLAYER1    1
#define TURN_WAITING    2

#define ARDUINO_ACK     'A'
#define ARDUINO_ON      1

typedef struct{
	char username0[128];
	char username1[128];
	int symbol0;
	int symbol1;
	int size;
	int type;
	int players;

    int turn;
    int next_turn;
    int matrix[9];

    int game_over;
    int game_win;
    int arduino_on;
    int arduino_first;
    arduino_t* arduino;

} game_t;

typedef struct {
    int socket_descriptor;
    int port;
    struct sockaddr_in direction;
    game_t* game;
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

void trim_query_line(client_t *client);
void delimit_query(client_t *client);
uint8_t process_query(client_t* client, server_t* server);

uint8_t send_text(client_t* client, const char* text);
uint8_t send_json(client_t* client, const char* text);
uint8_t send_error(client_t* client);
uint8_t set_params(const char* query, server_t* server, int function);
uint8_t set_game_params(char* key, char* value, server_t* server);
int check_game_win(server_t* server);
int check_game_over(server_t* server);
void init_game(server_t* server);
#endif