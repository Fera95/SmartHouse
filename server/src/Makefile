#CC = gcc
SRC = main.c
OUT = ../bin/SHserver2

LIBRASPIO = ../lib/libraspio.a
LIBSERVER = ../lib/libserver.a
LIBLOGGER = ../lib/libjvlogger.a

CFLAGS = -I../include
LDFLAGS = -L../lib 

main: $(SRC)
		$(CC) -o $(OUT) $(SRC) $(CFLAGS) $(LDFLAGS) $(LIBRASPIO) $(LIBSERVER) $(LIBLOGGER)

clean:
		rm main.o
		clear