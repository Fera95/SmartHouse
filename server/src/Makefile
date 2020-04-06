#CC = gcc
SRC = main.c
OUT = ../bin/SHserver

LIBRASPIO = ../lib/libraspio.a
LIBSERVER = ../lib/libserver.a

CFLAGS = -I../include
LDFLAGS = -L../lib 

main: $(SRC)
		$(CC) -o $(OUT) $(SRC) $(CFLAGS) $(LDFLAGS) $(LIBRASPIO) $(LIBSERVER) -pthread

clean:
		rm ../bin/smartHouseServer
		rm main.o
		clear