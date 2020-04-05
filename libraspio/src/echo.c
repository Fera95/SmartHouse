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



typedef struct {
	short input_pin;
	short output_pin;
	int duration;
} simon_params;

/** makes all leds used in the smartHouse project blink at the same time
 */
void* not_eternal_blink(int reps){
	// Blink forever!
	while (reps>0) {
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
		reps--;
	}
}

void* do_simon(void* params) {
	simon_params* current = (simon_params*) params;
	short in_pin = current->input_pin;
	short out_pin = current->output_pin;
	int d = current->duration;
	simon(in_pin, out_pin, d);
}

int main () {

	// SETUP
	pthread_t pt_bedroom;
	pthread_t pt_bathroom;
	pthread_t pt_hallway;
	pthread_t pt_studio;
	pthread_t pt_kitchen;

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
	simon_params* params_bedroom = (simon_params*) malloc(sizeof(simon_params));
	simon_params* params_bathroom = (simon_params*) malloc(sizeof(simon_params));
	simon_params* params_kitchen = (simon_params*) malloc(sizeof(simon_params));
	simon_params* params_hallway = (simon_params*) malloc(sizeof(simon_params));
	simon_params* params_studio = (simon_params*) malloc(sizeof(simon_params));

	int duration = 40000;

	params_bedroom->input_pin = door_bedroom;
	params_bedroom->output_pin = led_bedroom;
	params_bedroom->duration = duration;

	params_bathroom->input_pin = door_bathroom;
	params_bathroom->output_pin = led_bathroom;
	params_bathroom->duration = duration;

	params_kitchen->input_pin = door_kitchen;
	params_kitchen->output_pin = led_kitchen;
	params_kitchen->duration = duration;

	params_hallway->input_pin = door_hallway;
	params_hallway->output_pin = led_hallway;
	params_hallway->duration = duration;

	params_studio->input_pin = door_studio;
	params_studio->output_pin = led_studio;
	params_studio->duration = duration;

	pthread_create(&pt_bedroom, NULL, do_simon, (void*) params_bedroom);
	pthread_create(&pt_bathroom, NULL, do_simon, (void*) params_bathroom);
	pthread_create(&pt_hallway, NULL, do_simon, (void*) params_hallway);
	pthread_create(&pt_kitchen, NULL, do_simon, (void*) params_kitchen);
	pthread_create(&pt_studio, NULL, do_simon, (void*) params_studio);

	pthread_join(pt_bedroom, NULL);
	pthread_join(pt_bathroom, NULL);
	pthread_join(pt_hallway, NULL);
	pthread_join(pt_kitchen, NULL);
	pthread_join(pt_studio, NULL);
		
	return 0;
}
