CC = gcc
SRC = main.c
OUT = ../bin/SHserver

LIBSERVER = ../lib/libserver.a

CFLAGS = -I../include
LDFLAGS = -L../lib 

main: $(SRC)
		$(CC) -o $(OUT) $(SRC) $(CFLAGS) $(LDFLAGS) $(LIBSERVER)

clean:
		rm ../bin/smartHouseServer
		rm main.o
		clear