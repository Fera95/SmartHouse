#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/libraspio.h"

const char* ECHO = "echo ";
const char* IN = "in";
const char* OUT = "out";
const char* EXPO = " > /sys/class/gpio/export";
const char* PATH = " > /sys/class/gpio/gpio";
const char* READ = "/sys/class/gpio/gpio";
const char* SDIR = "/direction";
const char* SVAL = "/value";

/** Initializes a pin and sets it as input or output
 * \param short pin : the pin to initialize (Use pin name not pin number)
 * \param int mode: the status for the pin. The pinState enum allows for INPUT or OUTPUT
 */
void pinMode(short pin, int mode){
	char setup[256];
	
	char usr_pin[4];
	sprintf(usr_pin, "%d", pin);
	
	strcat(setup, ECHO);
	strcat(setup, usr_pin);
	strcat(setup, EXPO);
	
	//printf("%s\n", setup);
	system(setup);
	memset(setup, 0, 256);

	// Set pin as input or output
	if (mode==INPUT){
		char incmd[256];
		
		strcat(incmd, ECHO);
		strcat(incmd, IN);
		strcat(incmd, PATH);
		strcat(incmd, usr_pin);
		strcat(incmd, SDIR);
		
		//printf("%s\n", incmd);
		system(incmd);
		memset(incmd, 0, 256);
    } else {//if (mode==OUTPUT)
		char otcmd[256];
		
		strcat(otcmd, ECHO);
		strcat(otcmd, OUT);
		strcat(otcmd, PATH);
		strcat(otcmd, usr_pin);
		strcat(otcmd, SDIR);
		
		//printf("%s\n", otcmd);
		system(otcmd);
		memset(otcmd, 0, 256);
    }
}

/** Writes a 1 or 0 to a pin to set it's voltage to 3V3 or GND
 * \param short pin : the pin to initialize (Use pin name not pin number)
 * \param int value: the value for the pin. The pinValue enum allows for HIGH or LOW
 */
void digitalWrite (short pin, int value) {
	char usr_value[2];
	sprintf(usr_value, "%d", value);

	char usr_pin[4];
	sprintf(usr_pin, "%d", pin);
	
	char final[256];
	
	//replace_char(final, usr_pin, usr_value, ECHO, PATH, SVAL);
	strcat(final, ECHO);
	strcat(final, usr_value);
	strcat(final, PATH);
	strcat(final, usr_pin);
	strcat(final, SVAL);
	
	//printf("%s\n", final);
	system(final);
	memset(final, 0, 256);
}

/** Reads a 1 or 0 from a pin by reading it's value file
 * \param short pin : the pin to initialize (Use pin name not pin number)
 * \return int read: the value read in the pin. The pinValue enum allows for HIGH or LOW
 */
int digitalRead(short pin){
	char path[256];

	char usr_pin[4];
	sprintf(usr_pin, "%d", pin);

	strcat(path, READ);
	strcat(path, usr_pin);
	strcat(path, SVAL);

    FILE* file = fopen(path, "r");
    if(file==NULL){
        printf ("Pin not initialized. \n");
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

/** Turns a pin on and off.
 * \param pin the pin that will emit a blinking signal. Remember to set as OUTPUT
 * \param frecuency the recuency of the blink, in Hz.
 * \param duration for how long it is going to blink, in seconds.
 */
void blink(short pin, int frecuency, int duration){
    double T = 1000000/frecuency; // pass to us
	double active = duration*1000000; // pass to us
	
    while (active > 0) {
        digitalWrite(pin, HIGH);
        usleep(T);
        digitalWrite(pin, LOW);
        usleep(T);
        active-=2*T;
    }
    
}

/** makes a pin output what other pin reads. The repeater outputs what is read in the receiver 5us after
 * \param pin_receiver the pin that will receive the signal. Remember to set as INPUT
 * \param pin_repeater the pin that will output the signal. Remember to set as OUTPUT
 * \param duration for how long will this task be done, in seconds
 */
void simon (short pin_receiver, short pin_repeater, int duration) {
	int signal = 0;
	double active = duration*1000000; // pass to us

	while (active > 0) {
		signal = digitalRead (pin_receiver);
		usleep(5);
		digitalWrite(pin_repeater, signal);
		usleep(5);
		active-=10;
    }


}