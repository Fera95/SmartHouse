CC = gcc
SRC = main.c

LIBNAME = libraspio
LIBSO = ../lib/$(LIBNAME).a

OUT = ../bin/raspio

CFLAGS = -I../include
LDFLAGS = -L../lib 

#Create executables

executables:
		$(CC) -o $(OUT) $(SRC) $(CFLAGS) $(LDFLAGS) $(LIBSO)
		export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:./lib
		
clean:
		rm $(OUT)