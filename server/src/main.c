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
#include <pthread.h>
#include <jvlogger.h>
#include <libserver.h>
#include <libraspio.h>

server_t *server;
client_t *client;
int in_use;


void initialize_daemon(){
    pid_t pid;
    
    logg(1, "Daemon: SHserver is forking once");

    //Fork parent
    pid = fork();           
    
    //Error in forking
    if (pid < 0){           
        logg(1, "Daemon: SHserver failed first fork");
        exit(EXIT_FAILURE); 
    }
    
    //Success in forking, exit the parent
    if (pid > 0){           
        logg(1, "Daemon: SHserver completed first fork");
        exit(EXIT_SUCCESS); 
    }
    
    //Child becomes leader, otherwise ends the program
    if (setsid() < 0){      
        logg(1, "Daemon: SHserver child couldn't be leader");
        exit(EXIT_FAILURE); 
    }
    
    
    // Signal handling
    logg(1, "Daemon: SHserver handling signals");
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    
    // Set the file permissions
    umask(0);
    
    //Changes the directory to the root folder
    chdir("/"); 

    // Close all file descriptors opened
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--){
        close (x);
    }
    
    //Make logs
    logg(1, "Daemon: SHserver completed initializing daemon");
}


void close_socket(){
    logg(1, "+++ Killing +++");
    close_server(server);
    if(in_use){
        close_client(client);
    }
    kill(getpid(), SIGKILL);
}

/** Initialize pins of the GPIO
 */
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

int start_client() {
    //system("python3 ../client/py_socket.py"); // For non raspberry pi use
    system("python3 ./py_socket.py");
    return 0;
}

int main(int argc, char *argv[]) {
    int port = 1080;
    if(argc > 1) port = atoi(argv[1]);

    // init log
	start_logg();

    //init_pins();
    server = (server_t*) malloc(sizeof(server_t));
    client = (client_t*) malloc(sizeof(client_t));
    if(init_server(server, port)) exit(1);
    logg (3, "+++ Server listening on port ", itoc(port), " +++");
    printf("+++ Server listening on port %d +++", port);
    signal(SIGINT, close_socket);
        
    devices_t *my_leds;
    my_leds = (devices_t*) malloc(sizeof(devices_t));
    server->leds = my_leds;
    devices_t *my_doors;
    my_doors = (devices_t*) malloc(sizeof(devices_t));
    server->doors = my_doors;

    init_devices(server);

    //Start socket interphase
    pthread_t socket_client;
    if (pthread_create(&socket_client, NULL, (void*) &start_client, NULL) != 0) {
        logg(1, "+++ Error creating socket client +++");
    }
    
    while (1) {
        if(accept_client(server, client) == 0) {
            in_use=1;
            logg(3, "+++ New client received coming from IP ", itoc(*client->ip),  " +++");
            process_client(client, server);
            in_use=0;
            close_client(client);
        }
    }

    pthread_join(socket_client, NULL);
    close_server(server);
}
