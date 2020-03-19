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
#include <libserver.h>

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

uint8_t process_query(client_t *client, server_t *server) {
    char *query = client->buffer;
    printf("Client sent: %s\n", query);
    if(strcmp(query, "/dummy") == 0) {
        send_text(client, "Im dummy");
    } else if(strncmp(query, "/setup", 6) == 0) {
        uint8_t ret = set_params(query, server, 0);
        if(ret == TYPE_ERROR) send_json(client, "{\"Status\": \"Waiting\"}");
        else if(ret == SYMBOL_ERROR) send_json(client, "{\"Status\": \"Busy\"}");
        else if(ret == AMOUNT_ERROR) send_json(client, "{\"Status\": \"Full\"}");
        else send_json(client, "{\"Status\": \"Ok\"}");
    } else if(strncmp(query, "/move", 5) == 0) {
        uint8_t ret = set_params(query, server, 1);
        if(ret == POSITION_ERROR) send_json(client, "{\"Status\": \"Position full\"}");
        else send_json(client, "{\"Status\": \"Ok\"}");
    } else if(strncmp(query, "/restart", 8) == 0) {
        init_devices(server);
    } else {
        send_json(client, "{\"Status\": \"Ok\"}");
    }
}

uint8_t send_text(client_t *client, const char *text) {
    write(client->socket_descriptor, html_web_text, sizeof(html_web_text) - 1);
    write(client->socket_descriptor, text, strlen(text));
}
uint8_t send_json(client_t *client, const char *text) {
    write(client->socket_descriptor, html_web_json, sizeof(html_web_json) - 1);
    write(client->socket_descriptor, text, strlen(text));
}
uint8_t send_error(client_t *client) {
    write(client->socket_descriptor, html_web_error, sizeof(html_web_error) - 1);
}

void init_devices(server_t *server) {
    devices_t * init_device;
	init_device = (devices_t*) malloc (sizeof(devices_t));
    init_device = server->devices;
    init_device->bedroom = 0;
    init_device->bathroom = 0;
    init_device->hallway = 1;
    init_device->kitchen = 0;
    init_device->studio = 0;
}