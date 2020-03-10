#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libraspio.h>

							// 3V3 power
#define led_bedroom	2		// GPIO2
#define led_bathroom 3		// GPIO3
#define led_hallway	4		// GPIO4
							// GND
#define led_drums 17		// GPIO17
#define led_studio 27		// GPIO27
#define door_bedroom 22		// GPIO22
							// 3V3 power
#define door_bathroom 10	// GPIO10
#define door_hallway 9		// GPIO9
#define door_drums 11		// GPIO11
							// GND
							// GPIO0
#define door_studio 5		// GPIO5
							// GPIO6
							// GPIO13
							// GPIO19
							// GPIO26
							// GND

int main () {
	// SETUP
	pinMode(led_drums, OUTPUT);
	pinMode(led_studio, OUTPUT);
	pinMode(door_bedroom, INPUT);
	
	//blink(led_drums, 2, 5);

	for (int i = 0; i<5; i++) {
		digitalWrite(led_drums, HIGH);
		usleep(500000);
		digitalWrite(led_drums, LOW);
		usleep(500000);
	

	simon(door_bedroom, led_studio, 5);

	/* LOOP
	int loop = 1;
	while (0) 	{
		loop = 0;
	}*/
	
	return 0;
}