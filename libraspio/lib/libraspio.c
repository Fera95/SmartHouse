#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include "../include/libraspio.h"

char *EXPO = "/sys/class/gpio/export";
char *PATH = "/sys/class/gpio/gpio";
char *SDIR = "/direction";
char *SVAL = "/value";
char *OUT = "out";
char *IN = "in";

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

/** Turns a pin on and off.
 * \param pin the pin that will emit a blinking signal. Remember to set as OUTPUT
 * \param frecuency the recuency of the blink, in Hz.
 * \param duration for how long it is going to blink, in seconds.
 */
void blink(short pin, int frecuency, double duration) {
	int T = (int) 1000000/frecuency;
	duration *= 1000000;

	printf ("starting blink in pin %d\n", pin);

	while (duration > 0) {
		digitalWrite(pin, HIGH);
		usleep(T);
		digitalWrite(pin, LOW);
		usleep(T);
		duration -= (2*T);
	}
	printf ("done blinking\n");
}

/** makes a pin output what other pin reads. The repeater outputs what is read in the receiver 5us after
 * \param pin_receiver the pin that will receive the signal. Remember to set as INPUT
 * \param pin_repeater the pin that will output the signal. Remember to set as OUTPUT
 * \param duration for how long will this task be done, in seconds
 */
void simon(short pin_receiver, short pin_repeater, int duration) {
	int signal = 0;
	printf ("starting echo from pin %d to pin %d\n", pin_receiver, pin_repeater);

	while (duration > 0) {
		signal = digitalRead(pin_receiver);
		sleep(1);
		digitalWrite(pin_repeater, signal);
		sleep(1);
		duration -= 2;
	}
	printf ("done echoing\n");
}