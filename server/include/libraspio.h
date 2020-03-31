#ifndef libraspio
#define libraspio

enum pinValues {HIGH = 1, LOW = 0};
enum pinState {INPUT = 1, OUTPUT = 0};

void pinMode(short pin, int mode);

void digitalWrite (short pin, int value);

int digitalRead (short pin);

void blink(short pin, int frecuency, double duration);

void simon (short pin_receiver, short pin_repeater, int duration);

#endif