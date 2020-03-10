
#include "../include/libraspio.h"

enum pinValues {HIGH = 1, LOW = 0};
enum pinState {INPUT = 1, OUTPUT = 0};

int main () {
	// SETUP
    pinMode(13, OUTPUT);
	blink(13, 1, 5);

	// LOOP
	int loop = 1;
	while (0) 	{
		loop = 0;
	}
	
	return 0;
}