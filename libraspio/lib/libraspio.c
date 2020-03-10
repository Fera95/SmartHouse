#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MILL 1000000

//const char* gpio_access = "/sys/class/gpio/export";
//const char* gpio_direction = "/sys/class/gpio/";

enum pinValues {HIGH = 1, LOW = 0};
enum pinState {INPUT = 1, OUTPUT = 0};

void pinMode(short pin, int mode){
	
	// Activate pin
	const char* ECHO = "echo "; // usr_pin
	const char* EXPO = " > /sys/class/gpio/export";
	char setup[256];
	
	char usr_pin[4];
	sprintf(usr_pin, "%d", pin);
	
	strcat(setup, ECHO);
	strcat(setup, usr_pin);
	strcat(setup, EXPO);
	
	printf("%s\n", setup);
	memset(setup, 0, 256);

	// Set pin as input or output
	const char* IN = "in";
	const char* OUT = "out";
	const char* PATH = " > /sys/class/gpio/gpio"; //usr_pin
	const char* SDIR = "/direction";
	
	if (mode==INPUT){
		char incmd[256];
		
		strcat(incmd, ECHO);
		strcat(incmd, IN);
		strcat(incmd, PATH);
		strcat(incmd, usr_pin);
		strcat(incmd, SDIR);
		
		printf("%s\n", incmd);
		memset(incmd, 0, 256);
    } else {//if (mode==OUTPUT)
		char otcmd[256];
		
		strcat(otcmd, ECHO);
		strcat(otcmd, OUT);
		strcat(otcmd, PATH);
		strcat(otcmd, usr_pin);
		strcat(otcmd, SDIR);
		
		printf("%s\n", otcmd);
		memset(otcmd, 0, 256);
    }
}

void digitalWrite (int pin, int value) {
	char usr_value[2];
	sprintf(usr_value, "%d", value);

	char usr_pin[4];
	sprintf(usr_pin, "%d", pin);
	
	const char* ECHO = "echo "; //usr_value
	const char* PATH = " > /sys/class/gpio/gpio"; //usr_pin
	const char* SVAL = "/value";

	char final[256];
	
	//printf("echo %s > /sys/class/gpio/gpio%s/value\n", usr_value, usr_pin);
	
	//replace_char(final, usr_pin, usr_value, ECHO, PATH, SVAL);
	strcat(final, ECHO);
	strcat(final, usr_value);
	strcat(final, PATH);
	strcat(final, usr_pin);
	strcat(final, SVAL);
	
	system(final);
}

int digitalRead(const char* conf_path){
    FILE* file = fopen(conf_path, "r");
    if(file==NULL){
        printf ("Path to config not avaliable. \n");
        exit(EXIT_FAILURE); 
    }
    char line[256];
    int read;
    
    fgets(line, sizeof(line), file);
    read = atoi(line);
    
    //while (fgets(line, sizeof(line), file)) {
        //char* current = strtok (line, "\n");
        //read = atoi(current);
    //}
    fclose(file);
    return read;
} 

/** Generar un parpadeo. Establecer y desestablecer un valor binario en un pin.
 * 
 * \param pin el pin que va a parpadear. Debe estar en modo OUTPUT
 * \param frecuency la frecuencia a la que va a parpadear, en Hertz
 * \param duration la duración por la que va a parpadear, en segundos
 * 
 */
void blink(short pin, int frecuency, int duration){
    double time = 0;
    while (duration > 0) {
        time = 1/frecuency;
        digitalWrite(pin, HIGH);
        usleep(time*MILL);
        digitalWrite(pin, LOW);
        usleep(time*MILL);
        duration-=2*time;
    }
    
}
