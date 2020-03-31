#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include "../include/libserver.h"

char *EXPO = "/sys/class/gpio/export";
char *PATH = "/sys/class/gpio/gpio";
char *SDIR = "/direction";
char *SVAL = "/value";
char *OUT = "out";
char *IN = "in";

char html_web_error[] =
    "HTTP/1.1 200 Ok\r\n"
    "Content-Type: text/html; charset=UTF-8\r\n\r\n"
    "<!DOCTYPE html>\r\n"
    "<html><head><br><br><br><br><title>WebService</title>\r\n"
    "<style>body { background-color: #008080 }</style></head>\r\n"
    "<body><center><h1>Error 404 Not Found</h1><br>\r\n"
    "</center></body></html>\r\n";

char html_web_image[] =
    "HTTP/1.1 200 Ok\r\n"
    "Content-Type: image/png\r\n\r\n";

char html_web_text[] =
    "HTTP/1.1 200 Ok\r\n"
    "Access-Control-Allow-Headers\r\n"
    "Access-Control-Allow-Origin: *\r\n"
    "Content-Type: text/plain\r\n\r\n";

char html_web_file[] =
    "HTTP/1.1 200 Ok\r\n"
    "Content-Type: image/*\r\n\r\n";

char html_web_json[] =
    "HTTP/1.1 200 Ok\r\n"
    "Access-Control-Allow-Headers\r\n"
    "Access-Control-Allow-Origin: *\r\n"
    "Content-Type: application/json\r\n\r\n";

struct sockaddr_in get_direction(server_t *server) {
    struct sockaddr_in direction;
    direction.sin_family = AF_INET;
    direction.sin_port = htons(server->port);
    direction.sin_addr.s_addr = INADDR_ANY;
    return direction;
}

uint8_t bind_socket(server_t *server) {
    if (bind(server->socket_descriptor, (struct sockaddr *)& server->direction, sizeof(server->direction)) == -1) return 1;
    return 0;
}

uint8_t listen_server(server_t *server) {
    if (listen(server->socket_descriptor, MAX_CLIENTS) == -1) return 1;
    return 0;
}

uint8_t init_server(server_t *server, int port) {
    // Creates the server socket descriptor
    server->socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket_descriptor == -1) return SOCKET_ERROR;
    // Sets the port
    server->port = port;
    // Sets the sockaddr_in
    server->direction = get_direction(server);
    // Binds the server socket
    if(bind_socket(server)) {
        close(server->socket_descriptor);
        return BIND_ERROR;
    }
    // Sets the server socket to listen
    if(listen_server(server)) {
        close(server->socket_descriptor);
        return LISTEN_ERROR;
    }
    return 0;
}

uint8_t close_server(server_t *server) {
    printf("Closing server\n");
    close(server->socket_descriptor);
    return 0;
}

char *get_ip(client_t *client) {
    struct sockaddr_in *addr_in = (struct sockaddr_in *) &client->client_sockaddr;
    char *ip = inet_ntoa(addr_in->sin_addr);
    return ip;
}

uint8_t accept_client(server_t *server, client_t *client) {
    client->length = sizeof(client->client_sockaddr);
    client->socket_descriptor = accept(server->socket_descriptor,
                                       &client->client_sockaddr,
                                       &client->length);
    if(client->socket_descriptor == -1) {
        close(client->socket_descriptor);
        return ACCEPT_ERROR;
    }
    // Clears buffer
    memset(client->buffer, 0, BUFFER_SIZE);
    // Reads the incoming data
    read(client->socket_descriptor, client->buffer, BUFFER_SIZE);
    client->ip = get_ip(client);
    return 0;
}

uint8_t close_client(client_t *client) {
	close(client->socket_descriptor);
	return 0;
}

uint8_t process_client(client_t *client, server_t *server) {
	trim_query(client);				// First line
	delimit_query(client);			// Removes GET till space
	process_query(client, server);	// Process that query
}

void trim_query(client_t *client) {
    int i = 0;
    char *buffer = client->buffer;
    while(buffer[i] != '\0') {
        if(buffer[i] == '\n') buffer[i] = '\0';
        ++i;
    }
}

void delimit_query(client_t *client) {
    char *buffer = client->buffer;
    int i = 0;
    int s = 0;
    int in_query = 0;
    while(buffer[i] != '\0') {
        if(in_query == 0 && buffer[i] == '/') {
            s = i; //sets start
            in_query = 1;
        }
        if(in_query == 1 && buffer[i] == ' ') {
            buffer[i] = '\0';
            buffer[i + 1] = '\0';
            break;
        }
        ++i;
    }
    memcpy(client->buffer, buffer + s, sizeof(buffer + s));
}

uint8_t set_params(const char *query, server_t *server, int function) {
    int i = 0;
    char key[128];
    char value[128];
    int a = 0;
    uint8_t retval = 0;
    while(query[i]) {
        if(query[i++] == '?') a++;
        if (a == 2) break;
    }
    while(query[i]) {
        int ii = 0;
        while(query[i] && (query[i] != '=')) {
            key[ii] = query[i];
            ii++;
            i++;
        }
        key[ii] = '\0';
        ii = 0;
        i++;
        while(query[i] && (query[i] != '&')) {
            value[ii] = query[i];
            ii++;
            i++;
        }
        value[ii] = '\0';
        i++;
        //printf("Param, key: %s, value: %s\n", key, value);
        if(retval) return retval;
    }
    return 0;
}

/** returns the JSON that matches the status of the doors.
 * \param code a binary-made 5 bit code to select the correct json
 */
const char * jsonPicker (int code) {
	switch (code) {
		case  0: return("{ \"led_1\": 0, \"led_2\": 0, \"led_3\": 0, \"led_4\": 0, \"led_5\": 0 }");
		case  1: return("{ \"led_1\": 0, \"led_2\": 0, \"led_3\": 0, \"led_4\": 0, \"led_5\": 1 }");
		case  2: return("{ \"led_1\": 0, \"led_2\": 0, \"led_3\": 0, \"led_4\": 1, \"led_5\": 0 }");
		case  3: return("{ \"led_1\": 0, \"led_2\": 0, \"led_3\": 0, \"led_4\": 1, \"led_5\": 1 }");
		case  4: return("{ \"led_1\": 0, \"led_2\": 0, \"led_3\": 1, \"led_4\": 0, \"led_5\": 0 }");
		case  5: return("{ \"led_1\": 0, \"led_2\": 0, \"led_3\": 1, \"led_4\": 0, \"led_5\": 1 }");
		case  6: return("{ \"led_1\": 0, \"led_2\": 0, \"led_3\": 1, \"led_4\": 1, \"led_5\": 0 }");
		case  7: return("{ \"led_1\": 0, \"led_2\": 0, \"led_3\": 1, \"led_4\": 1, \"led_5\": 1 }");
		
		case  8: return("{ \"led_1\": 0, \"led_2\": 1, \"led_3\": 0, \"led_4\": 0, \"led_5\": 0 }");
		case  9: return("{ \"led_1\": 0, \"led_2\": 1, \"led_3\": 0, \"led_4\": 0, \"led_5\": 1 }");
		case 10: return("{ \"led_1\": 0, \"led_2\": 1, \"led_3\": 0, \"led_4\": 1, \"led_5\": 0 }");
		case 11: return("{ \"led_1\": 0, \"led_2\": 1, \"led_3\": 0, \"led_4\": 1, \"led_5\": 1 }");
		case 12: return("{ \"led_1\": 0, \"led_2\": 1, \"led_3\": 1, \"led_4\": 0, \"led_5\": 0 }");
		case 13: return("{ \"led_1\": 0, \"led_2\": 1, \"led_3\": 1, \"led_4\": 0, \"led_5\": 1 }");
		case 14: return("{ \"led_1\": 0, \"led_2\": 1, \"led_3\": 1, \"led_4\": 1, \"led_5\": 0 }");
		case 15: return("{ \"led_1\": 0, \"led_2\": 1, \"led_3\": 1, \"led_4\": 1, \"led_5\": 1 }");
		
		case 16: return("{ \"led_1\": 1, \"led_2\": 0, \"led_3\": 0, \"led_4\": 0, \"led_5\": 0 }");
		case 17: return("{ \"led_1\": 1, \"led_2\": 0, \"led_3\": 0, \"led_4\": 0, \"led_5\": 1 }");
		case 18: return("{ \"led_1\": 1, \"led_2\": 0, \"led_3\": 0, \"led_4\": 1, \"led_5\": 0 }");
		case 19: return("{ \"led_1\": 1, \"led_2\": 0, \"led_3\": 0, \"led_4\": 1, \"led_5\": 1 }");
		case 20: return("{ \"led_1\": 1, \"led_2\": 0, \"led_3\": 1, \"led_4\": 0, \"led_5\": 0 }");
		case 21: return("{ \"led_1\": 1, \"led_2\": 0, \"led_3\": 1, \"led_4\": 0, \"led_5\": 1 }");
		case 22: return("{ \"led_1\": 1, \"led_2\": 0, \"led_3\": 1, \"led_4\": 1, \"led_5\": 0 }");
		case 23: return("{ \"led_1\": 1, \"led_2\": 0, \"led_3\": 1, \"led_4\": 1, \"led_5\": 1 }");
		
		case 24: return("{ \"led_1\": 1, \"led_2\": 1, \"led_3\": 0, \"led_4\": 0, \"led_5\": 0 }");
		case 25: return("{ \"led_1\": 1, \"led_2\": 1, \"led_3\": 0, \"led_4\": 0, \"led_5\": 1 }");
		case 26: return("{ \"led_1\": 1, \"led_2\": 1, \"led_3\": 0, \"led_4\": 1, \"led_5\": 0 }");
		case 27: return("{ \"led_1\": 1, \"led_2\": 1, \"led_3\": 0, \"led_4\": 1, \"led_5\": 1 }");
		case 28: return("{ \"led_1\": 1, \"led_2\": 1, \"led_3\": 1, \"led_4\": 0, \"led_5\": 0 }");
		case 29: return("{ \"led_1\": 1, \"led_2\": 1, \"led_3\": 1, \"led_4\": 0, \"led_5\": 1 }");
		case 30: return("{ \"led_1\": 1, \"led_2\": 1, \"led_3\": 1, \"led_4\": 1, \"led_5\": 0 }");
		case 31: return("{ \"led_1\": 1, \"led_2\": 1, \"led_3\": 1, \"led_4\": 1, \"led_5\": 1 }");
		default: return("{\"Status\": \"Ok\"}");
	}
}

uint8_t process_query(client_t *client, server_t *server) {
    char *query = client->buffer;
    printf("Client sent: %s\n", query);
    const char s[2] = ":";
	char str[80];
	strcpy(str, query);

    // Parse expected query
	char *token;
    token = strtok(str, s);
	server->leds->bedroom = atoi(token);
	token = strtok(NULL, s);
	server->leds->bathroom = atoi(token);
	token = strtok(NULL, s);
	server->leds->hallway = atoi(token);
	token = strtok(NULL, s);
	server->leds->kitchen = atoi(token);
	token = strtok(NULL, s);
	server->leds->studio = atoi(token);

    digitalWrite(led_bedroom, server->leds->bedroom);
    digitalWrite(led_bathroom, server->leds->bathroom);
    digitalWrite(led_hallway, server->leds->hallway);
    digitalWrite(led_kitchen, server->leds->kitchen);
    digitalWrite(led_studio, server->leds->studio);

    server->doors->bedroom = digitalRead(door_bedroom);
    server->doors->bathroom = digitalRead(door_bathroom);
    server->doors->hallway = digitalRead(door_hallway);
    server->doors->kitchen = digitalRead(door_kitchen);
    server->doors->studio = digitalRead(door_studio);

    system("clear");
	printf("led bedroom: %d\n", server->leds->bedroom);
	printf("led bathroom: %d\n", server->leds->bathroom);
	printf("led hallway: %d\n", server->leds->hallway);
	printf("led kitchen: %d\n", server->leds->kitchen);
	printf("led studio: %d\n", server->leds->studio);
/*
    server->doors->bedroom = 0;// digitalRead(door_bedroom);
    server->doors->bathroom = 1;// digitalRead(door_bathroom);
    server->doors->hallway = 0;//digitalRead(door_hallway);
    server->doors->kitchen = 1;//digitalRead(door_kitchen);
    server->doors->studio = 1;//digitalRead(door_studio);
*/
    if(strcmp(query, "/dummy") == 0) {
        send_text(client, "Im dummy");
    } else if(strncmp(query, "/restart", 8) == 0) {
        init_devices(server);
    } else {
        const char * json_msg = jsonPicker( server->doors->bedroom*16+
                                            server->doors->bathroom*8+
                                            server->doors->hallway*4+
                                            server->doors->kitchen*2+
                                            server->doors->studio*1);
        send_json(client, json_msg);
    }
}

uint8_t send_text(client_t *client, const char *text) {
    write(client->socket_descriptor, html_web_text, sizeof(html_web_text) - 1);
    write(client->socket_descriptor, text, strlen(text));
}
uint8_t send_json(client_t *client, const char *text) {
    //write(client->socket_descriptor, html_web_json, sizeof(html_web_json) - 1);
    write(client->socket_descriptor, text, strlen(text));
}
uint8_t send_error(client_t *client) {
    write(client->socket_descriptor, html_web_error, sizeof(html_web_error) - 1);
}

void init_devices(server_t *server) {
    server->leds->bedroom = 0;
    server->leds->bathroom = 0;
    server->leds->hallway = 1;
    server->leds->kitchen = 0;
    server->leds->studio = 0;

    server->doors->bedroom = 0;  // digitalRead(door_bedroom);
    server->doors->bathroom = 1; // digitalRead(door_bathroom);
    server->doors->hallway = 0;  //digitalRead(door_hallway);
    server->doors->kitchen = 0;  //digitalRead(door_kitchen);
    server->doors->studio = 0;   //digitalRead(door_studio);
}

/** Writes a int to a file, overwritting the existing file
 * \param data the data to be written. An int
 * \param write_path the path to the file
 */
void write_int(int data, char *write_path) {
	FILE *fp;
	char *newline = "\n";
	fp = fopen(write_path, "w"); // append mode

	if (fp == NULL) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	fprintf(fp, "%d", data);

	fclose(fp);
}

 // =================================== GPIO LIB ===================================

/** Writes a char* to a file, overwritting the existing file
 * \param data the data to be written. A char *
 * \param write_path the path to the file
 */
void write_char(char *data, char *write_path) {
	FILE *fp;
	fp = fopen(write_path, "w"); // write mode

	if (fp == NULL) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	fprintf(fp, "%s", data);

	fclose(fp);
}

void digitalWrite(short pin, int value) {
	char usr_value[2];
	sprintf(usr_value, "%d", value);

	char usr_pin[4];
	sprintf(usr_pin, "%d", pin);

	char final[256];
	memset(final, 0, 256);
	strcat(final, PATH);
	strcat(final, usr_pin);
	strcat(final, SVAL);

	//printf("%s\n", final);
	write_int((int) value, final);
	memset(final, 0, 256);
}

/** Reads a 1 or 0 from a pin by reading it's value file
 * \param pin : the pin to initialize (Use pin name not pin number)
 * \return read: the value read in the pin. The pinValue enum allows for HIGH or LOW
 */
int digitalRead(short pin) {
	char usr_pin[4];
	sprintf(usr_pin, "%d", pin);

	char path[256];
	memset(path, 0, 256);
	strcat(path, PATH);
	strcat(path, usr_pin);
	strcat(path, SVAL);

	FILE *file = fopen(path, "r");
	if (file == NULL)
	{
		printf("Pin not initialized. \n");
		exit(EXIT_FAILURE);
	}

	char line[256];
	fgets(line, sizeof(line), file);
	int read = atoi(line);

	fclose(file);
	memset(line, 0, 256);
	memset(path, 0, 256);

	return read;
}


/** Initializes a pin and sets it as input or output
 * \param pin : the pin to initialize (Use pin name not pin number)
 * \param mode: the status for the pin. The pinState enum allows for INPUT or OUTPUT
 */
void pinMode(short pin, int mode) {
	char usr_pin[4];
	sprintf(usr_pin, "%d", pin);
	write_int((int) pin, EXPO);

	// Set pin as input or output
	if (mode == INPUT) {
		char incmd[256];
		memset(incmd, 0, 256);
		strcat(incmd, PATH);
		strcat(incmd, usr_pin);
		strcat(incmd, SDIR);

		//printf("%s\n", incmd);
		write_char(IN, incmd);
		memset(incmd, 0, 256);
	}
	else { //if (mode==OUTPUT)
		char otcmd[256];
		memset(otcmd, 0, 256);
		strcat(otcmd, PATH);
		strcat(otcmd, usr_pin);
		strcat(otcmd, SDIR);

		//printf("%s\n", otcmd);
		write_char(OUT, otcmd);
		memset(otcmd, 0, 256);
	}
}
