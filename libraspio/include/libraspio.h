#ifndef libraspio
#define libraspio

enum pinValues {HIGH = 1, LOW = 0};
enum pinState {INPUT = 1, OUTPUT = 0};

// code supports 255 level of brightness because I'm not chaning all the logic to use stdbool
typedef struct {
	uint8_t bedroom;
	uint8_t bathroom;
	uint8_t hallway;
	uint8_t kitchen;
	uint8_t studio;
} devices_t;

void pinMode(short pin, int mode);

void digitalWrite (short pin, int value);

int digitalRead (short pin);

void blink(short pin, int frecuency, double duration);

void simon (short pin_receiver, short pin_repeater, int duration);

#endif