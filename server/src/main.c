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
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <sched.h> /* For clone */
#include <signal.h> /* For SIGCHLD */
#include <sys/wait.h> /* For wait */
#include <time.h>
#include <stdarg.h>
#include <sys/syscall.h> // For call to gettid
#include <libserver.h>
#include <libraspio.h>

server_t *server;
client_t *client;
int in_use;

void close_socket(){
    printf("+++ Killing +++\n");
    close_server(server);
    if(in_use){
        close_client(client);
    }
    kill(getpid(), SIGKILL);
}

void init_pins () {
	pinMode(led_bedroom, OUTPUT);
	pinMode(led_bathroom, OUTPUT);
	pinMode(led_hallway, OUTPUT);
	pinMode(led_kitchen, OUTPUT);
	pinMode(led_studio, OUTPUT);
	
	pinMode(door_bedroom, INPUT);
	pinMode(door_bathroom, INPUT);
	pinMode(door_hallway, INPUT);
	pinMode(door_kitchen, INPUT);
	pinMode(door_studio, INPUT);
} 


int main(int argc, char *argv[]) {
    int port = 8080;
    if(argc > 1) port = atoi(argv[1]);

    //init_pins();
    server = (server_t*) malloc(sizeof(server_t));
    client = (client_t*) malloc(sizeof(client_t));
    if(init_server(server, port)) exit(1);
    printf("+++ Now listening on port %d +++\n", port);
    signal(SIGINT, close_socket);
        
    devices_t *my_leds;
    my_leds = (devices_t*) malloc(sizeof(devices_t));
    server->leds = my_leds;
    devices_t *my_doors;
    my_doors = (devices_t*) malloc(sizeof(devices_t));
    server->doors = my_doors;

    init_devices(server);
    
    while (1) {
        if(accept_client(server, client) == 0) {
            in_use=1;
            printf("+++ New client received coming from IP %s +++\n", client->ip);
            process_client(client, server);
            in_use=0;
            close_client(client);
        }
    }
    close_server(server);
}
