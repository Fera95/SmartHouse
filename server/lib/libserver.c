#include <stdio.h>
#include <stdlib.h>
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
#include <libarduinocomms.h>

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
    trim_query_line(client);    // First line
    delimit_query(client);      // Removes GET till space
    process_query(client, server);      // Processes that query
}
uint8_t close_server(server_t *server) {
    printf("Closing server\n");
    close(server->socket_descriptor);
    return 0;
}

void trim_query_line(client_t *client) {
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

uint8_t set_game_params(char *key, char *value, server_t *server) {
    if(server->game->players > 1) return AMOUNT_ERROR;
    uint8_t retval = 0;
    if(strcmp(key, "username") == 0) { // Sets the username
        printf("Setting the username\n");
        if(server->game->players == 0) {
            strcpy(server->game->username0, value);
        } else if(server->game->players == 1) {
            strcpy(server->game->username1, value);
        }
    } else if(strcmp(key, "size") == 0) {
        // TODO: Send it to arduino, for it to know the start
        if(server->game->size == -1) {
            server->game->size = atoi(value);
            char to_send[8];
            sprintf(to_send, "s%d\n", server->game->size);
            if(ARDUINO_ON) {
                uint8_t n = arduino_sendstring(server->game->arduino, to_send);
            }
        }
    } else if(strcmp(key, "type") == 0) {
        int type = atoi(value);
        if(server->game->players == 0) {
            server->game->type = type;
        } else {
            if(server->game->type == TYPE_USERXPC) {
                strcpy(server->game->username1, "PC");
                retval = AMOUNT_ERROR;
                return retval;
            } else if(type == TYPE_USERXPC) {
                strcpy(server->game->username1, "Not assigned");
                retval = TYPE_ERROR;
                return retval;
            }

        }
    } else if(strcmp(key, "symbol") == 0) {
        int symbol = atoi(value);
        if(server->game->symbol0 == symbol) {
            retval = SYMBOL_ERROR; // Already using that symbol
            if(server->game->players == 0) {
                strcpy(server->game->username0, "Not assigned");
            } else if(server->game->players == 1) {
                strcpy(server->game->username1, "Not assigned");
            }
            return retval;
        } else {
            if(server->game->players == 0) {
                server->game->symbol0 = symbol;
                server->game->players++;
                if(server->game->type == TYPE_USERXPC) { // Start the game already!
                    printf("Starting game\n");
                    strcpy(server->game->username1, "PC");

                    if(symbol == 0) {
                        server->game->symbol1 = 1;
                    } else if(symbol == 1) {
                        server->game->symbol1 = 2;
                    } else if(symbol == 2) {
                        server->game->symbol1 = 0;
                    }

                }
            } else if(server->game->players == 1) {
                server->game->symbol1 = symbol;
                server->game->players++;
            }
        }
    }
    printf("Assigned %s value\n", key);
    return retval;
}

uint8_t send_status(client_t *client, server_t *server) { // This updates the status too
    game_t *game = server->game;
    char str[64] = {0};
    int i = 0;
    int index = 0;
    // Strings the matrix
    for (i = 0; i < 8; i++) index += sprintf(&str[index], "%d,", server->game->matrix[i]);
    sprintf(&str[index], "%d", server->game->matrix[i]);

    char buffer[512];
    // Gets the username
    char *username;
    if(server->game->turn == TURN_PLAYER0) {
        if((server->game->type == TYPE_USERXUSER && server->game->players == 1)) {
            username = "Not assigned";
        } else {
            username = server->game->username0;
        }
    } else if(server->game->turn == TURN_PLAYER1) username = server->game->username1;
    else username = "Waiting";
    // Gets the game state

    if(game->game_over == 0) {
        int game_win =  check_game_win(server);
        int game_over = check_game_over(server);
        int game_done = game_win != -1 || game_over == 1;
        game->game_over = game_done; // TODO: Check
        game->game_win = game_win;
    }


    // printf("Game win: %d\n", game_win);
    // printf("Game over: %d\n", game_over);

    sprintf(buffer, "{\"Turn\": \"%s\", \"Matrix\": [%s], \"Username0\":\"%s\", \"Username1\":\"%s\",\"Symbol0\": %d, \"Symbol1\":%d, \"State\":\"%s\"}",
            username, str,
            server->game->username0, server->game->username1,
            server->game->symbol0, server->game->symbol1,
            server->game->game_over ? "GameOver" : "Play");
    //printf("%s\n", buffer);
    send_json(client, buffer);

    // Read from arduino to see if it already finished
    int arduino_on = 0; // TODOTODOTODO Should read from arduino
    // if(ARDUINO_ON) {
    //     if(game->arduino_on == 1){ // Check if it finished
    //         uint8_t n = arduino_readuntil(server->game->arduino, buffer, ARDUINO_ACK);
    //         if(n > 0 && buffer[n - 1] == ARDUINO_ACK) {
    //             printf("Read %d bytes\n", n);
    //             arduino_on = 0;
    //             game->arduino_on = 0;
    //         } else {
    //             arduino_on = 1; // Not finished
    //         }
    //     }
    //     else{
    //         arduino_on = 0;
    //     }
    // }

    if(!arduino_on && game->arduino_first == 0) { // Arduino has finished, signal should only be sent when the algorithm is over
        //printf("Entering aarduino\n");
        if(game->game_over == 0) { // Normal logic
            server->game->turn = server->game->next_turn;
            if(server->game->turn == TURN_PLAYER1 && server->game->type == TYPE_USERXPC) {
                // Make movement from PC
                while(1) {
                    int j = rand() % 9;
                    if(server->game->matrix[j] == 3) { // Free space
                        server->game->matrix[j] = server->game->symbol1;
                        char to_send[8];
                        sprintf(to_send, "%d%d\n", server->game->symbol1, j);
                        if(ARDUINO_ON) {
                            uint8_t n = arduino_sendstring(server->game->arduino, to_send);
                            game->arduino_on = 1; // Arduino is now on
                            printf("Sending %s\n", to_send);
                        }
                        break;
                    }
                }
                server->game->turn = TURN_WAITING;
                server->game->next_turn = TURN_PLAYER0;
            }
        } else if(game->game_over == 1 && game->turn != TURN_WAITING) {
            printf("Game over and sending it to arduino\n");
            if(game->game_win != -1) { // Win type
                char to_send[8];
                sprintf(to_send, "w%d\n", game->game_win);
                if(ARDUINO_ON) {
                    uint8_t n = arduino_sendstring(server->game->arduino, to_send);
                    game->arduino_on = 1;
                }
            }
            game->game_over = 2;
        } else if(game->game_over == 1 && game->turn == TURN_WAITING) { // Set to not waiting
            printf("Game over and not sending it to arduino\n");
            game->turn = 69420; // random number not turn waiting
        } else if(game->game_over == 2){
            printf("Game done!\n");
            arduino_sendstring(server->game->arduino, "r\nr\nr\n");
            arduino_sendstring(server->game->arduino, "r\nr\nr\n");
            arduino_sendstring(server->game->arduino, "r\n");
            //init_game(server);
            game->game_over = 3;
        }
    } else if(game->arduino_first == 1) {
        server->game->turn = server->game->turn;
    } else {
        server->game->turn = TURN_WAITING;
    }
}
// Asumes coming move is correct and enabled
uint8_t make_move(char *key, char *value, server_t *server) {
    if(strncmp(key, "position", 8) == 0) {
        int position = atoi(value);
        if(server->game->matrix[position] == 3) { // Not in use
            int symbol = 3;
            if(server->game->turn == TURN_PLAYER0) {
                symbol = server->game->symbol0;
                server->game->next_turn = TURN_PLAYER1; // Redundancy, maybe
            } else if(server->game->turn == TURN_PLAYER1) {
                symbol = server->game->symbol1;
                server->game->next_turn = TURN_PLAYER0; // Redundancy, maybe
            }
            server->game->matrix[position] = symbol;
            server->game->turn = TURN_WAITING;
            server->game->arduino_first = 0;
            // TODOTODOTODO: Send to arduino
            char to_send[8];
            sprintf(to_send, "%d%d\n", symbol, position);
            if(ARDUINO_ON) {
                uint8_t n = arduino_sendstring(server->game->arduino, to_send);
                printf("Sending %s\n", to_send);
                server->game->arduino_on = 1;
            }
        } else {
            return POSITION_ERROR;
        }
    }
    return 0;
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
        if(function == 0) retval = set_game_params(key, value, server);
        else if(function == 1) retval = make_move(key, value, server);
        if(retval) return retval;
    }
    return 0;
}


uint8_t process_query(client_t *client, server_t *server) {
    char *query = client->buffer;
    if(strcmp(query, "/dummy") == 0) {
        send_text(client, "Im dummy");
    } else if(strncmp(query, "/setup", 6) == 0) {
        uint8_t ret = set_params(query, server, 0);
        if(ret == TYPE_ERROR) send_json(client, "{\"Status\": \"Waiting\"}");
        else if(ret == SYMBOL_ERROR) send_json(client, "{\"Status\": \"Busy\"}");
        else if(ret == AMOUNT_ERROR) send_json(client, "{\"Status\": \"Full\"}");
        else send_json(client, "{\"Status\": \"Ok\"}");
    } else if(strncmp(query, "/game", 5) == 0) {
        send_status(client, server);
    } else if(strncmp(query, "/move", 5) == 0) {
        uint8_t ret = set_params(query, server, 1);
        if(ret == POSITION_ERROR) send_json(client, "{\"Status\": \"Position full\"}");
        else send_json(client, "{\"Status\": \"Ok\"}");
    } else if(strncmp(query, "/restart", 8) == 0) {
        init_game(server);
    } else {
        send_json(client, "{\"Status\": \"Ok\"}");
    }
}

int check_game_win(server_t *server) {
    game_t *game = server->game;
    int *game_matrix = game->matrix;

    int i = 0;
    int symbol = 0;
    int retval = -1;
    for(; i < 3; ++i) { // Check rows
        symbol = game_matrix[3 * i];
        if(symbol != 3) {
            if(game_matrix[3 * i + 1] == symbol && game_matrix[3 * i + 2] == symbol) {
                retval = i;
                game_matrix[3 * i] = symbol + 4;
                game_matrix[3 * i + 1] = symbol + 4;
                game_matrix[3 * i + 2] = symbol + 4;
                return retval;
            }
        }
    }
    i = 0;
    for(; i < 3; ++i) { // Check columns
        symbol = game_matrix[i];
        if(symbol != 3) {
            if(game_matrix[i + 3] == symbol && game_matrix[i + 6] == symbol) {
                retval = i + 3;
                game_matrix[i] = symbol + 4;
                game_matrix[i + 3] = symbol + 4;
                game_matrix[i + 6] = symbol + 4;
                return retval;
            }
        }
    }
    // Check diagonal 1
    symbol = game_matrix[0];
    if(symbol != 3) {
        if(game_matrix[4] == symbol && game_matrix[8] == symbol) {
            retval = 6;
            game_matrix[0] = symbol + 4;
            game_matrix[4] = symbol + 4;
            game_matrix[8] = symbol + 4;
            return retval;
        }
    }
    // Check diagonal 2
    symbol = game_matrix[2];
    if(symbol != 3) {
        if(game_matrix[4] == symbol && game_matrix[6] == symbol) {
            retval = 7;
            game_matrix[2] = symbol + 4;
            game_matrix[4] = symbol + 4;
            game_matrix[6] = symbol + 4;
            return retval;
        }
    }
    return retval;


}

int check_game_over(server_t *server) {
    game_t *game = server->game;
    int *game_matrix = game->matrix;
    int retval = 1;
    for(int i = 0; i < 9; ++i) {
        if(game_matrix[i] == 3) {
            retval = 0;
            break;
        }
    }
    return retval;
}

void init_game(server_t *server) {
    game_t *game;
    game = server->game;
    strcpy(game->username0, "Not assigned");
    strcpy(game->username1, "Not assigned");
    game->size = -1;
    game->type = -1;
    game->players = 0;
    game->symbol0 = -1;
    game->symbol1 = -1;
    game->game_over = 0;
    game->game_win = -1;
    game->turn = TURN_PLAYER0;
    game->next_turn = TURN_PLAYER1;
    game->arduino_on = 0;
    game->arduino_first = 1;
    for(int i = 0; i < 9; ++i) game->matrix[i] = 3;
}