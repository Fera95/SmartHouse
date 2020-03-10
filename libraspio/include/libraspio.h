#ifndef libraspio
#define libraspio

void pinMode(short pin, int mode);

void digitalWrite (short pin);

void digitalRead (short pin);

void blink(short pin, int frecuency, int duration);

#endif