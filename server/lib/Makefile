#CC = gcc
AR = ar rv
RL = ranlib
NM = nm -s
LD = ld -o

LIBNAME = libraspio
LIBSRC = $(LIBNAME).c
LIBA = $(LIBNAME).a
LIBO = $(LIBNAME).o

SERVER = libserver
SERVER_SRC = $(SERVER).c
SERVER_LIB = $(SERVER).a
SERVER_OBJ = $(SERVER).o

all: $(SERVER_SRC) $(LIBSRC)
		make lib_raspio
		make lib_server

lib_raspio:
		$(CC) -c $(LIBSRC)
		$(AR) $(LIBA) $(LIBO)
		$(RL) $(LIBA)
		$(NM) $(LIBA)

lib_server:
		$(CC) -c $(SERVER_SRC)
		$(AR) $(SERVER_LIB) $(SERVER_OBJ)
		$(RL) $(SERVER_LIB)
		$(NM) $(SERVER_LIB)



clean:
		rm *.o
