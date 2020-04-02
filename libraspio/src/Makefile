#CC = gcc
#
SRC = main.c

LIBNAME = libraspio
LIBA = ../lib/$(LIBNAME).a

OUTX = ../bin/raspiox86
OUT = ../bin/raspio

CFLAGS = -I../include
LDFLAGS = -L../lib 


raspio:
		$(CC) -o $(OUT) $(SRC) $(CFLAGS) $(LDFLAGS) $(LIBA) -pthread
		
clean:
		rm $(OUT)
