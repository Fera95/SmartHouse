#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <libraspio.h>

							// 3V3 power
#define led_kitchen	2		// GPIO2
#define led_hallway 3		// GPIO3
#define led_bedroom	4		// GPIO4
							// GND
#define led_bathroom 17		// GPIO17
#define led_studio 27		// GPIO27
#define door_studio 22		// GPIO22
							// 3V3 power
#define door_bathroom 10	// GPIO10
#define door_bedroom 9		// GPIO9
#define door_kitchen 11		// GPIO11
							// GND
#define door_hallway 0		// GPIO0
							// GPIO5
							// GPIO6
							// GPIO13
							// GPIO19
							// GPIO26
							// GND

/** makes all leds used in the smartHouse project blink at the same time
 */
void* eternal_blink(){
	// Blink forever!
	while (1) {
		digitalWrite(led_bedroom, HIGH);
		digitalWrite(led_bathroom, HIGH);
		digitalWrite(led_hallway, HIGH);
		digitalWrite(led_kitchen, HIGH);
		digitalWrite(led_studio, HIGH);
		sleep(1);
		digitalWrite(led_bedroom, LOW);
		digitalWrite(led_bathroom, LOW);
		digitalWrite(led_hallway, LOW);
		digitalWrite(led_kitchen, LOW);
		digitalWrite(led_studio, LOW);
		sleep(1);
	}
}

/** makes all leds used in the smartHouse project blink at the same time
 */
void* eternal_write(){
	devices_t* update;
	update = (devices_t*) malloc(sizeof(devices_t));
	while (1) {
		//TODO: read_data(update); // fill struct with current data
		digitalWrite(led_bedroom, update->bedroom);
		digitalWrite(led_bathroom, update->bathroom);
		digitalWrite(led_hallway, update->hallway);
		digitalWrite(led_kitchen, update->kitchen);
		digitalWrite(led_studio, update->studio);
		sleep(1);
	}
}

void* eternal_read () {
	while (1){
		system("clear");
		printf(" bedroom door is: %d\n", digitalRead(door_bedroom));
		printf("bathroom door is: %d\n", digitalRead(door_bathroom));
		printf(" hallway door is: %d\n", digitalRead(door_hallway));
		printf(" kitchen door is: %d\n", digitalRead(door_kitchen));
		printf("  studio door is: %d\n", digitalRead(door_studio));
		//send_data();
	}
}

int main () {

	// SETUP
	pthread_t leds;
	pthread_t doors;

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

	// LOOP

	if (pthread_create(&leds, 0, &eternal_blink, NULL));
		printf("Error creating thread leds\n");
	if (pthread_create(&doors, 0, &eternal_read, NULL));
		printf("Error creating thread doors\n");

	pthread_join(leds, NULL);
	pthread_join(doors, NULL);
	
	return 0;
}
