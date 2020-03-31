#CC = gcc -c
AR = ar rv
RL = ranlib
NM = nm -s
LD = ld -o

SERVER = libserver
SERVER_LIB = $(SERVER).a
SERVER_SRC = $(SERVER).c
SERVER_OBJ = $(SERVER).o

all: $(SERVER_SRC) $(LIBSRC)
		make lib_server

lib_server:
		$(CC) -c $(SERVER_SRC)
		$(AR) $(SERVER_LIB) $(SERVER_OBJ)
		$(RL) $(SERVER_LIB)
		$(NM) $(SERVER_LIB)

clean:
		rm *.o
