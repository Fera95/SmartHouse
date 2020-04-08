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

LOGGER = jvlogger
LOGGER_SRC = $(LOGGER).c
LOGGER_OBJ = $(LOGGER).o
LOGGER_LIB = lib$(LOGGER).a

all: $(SERVER_SRC) $(LIBSRC)
		make lib_raspio
		make lib_server
		make lib_jvlogger
		make clean

lib_raspio:
		$(CC) -c $(LIBSRC)
		$(AR) $(LIBA) $(LIBO)
		$(RL) $(LIBA)
		#$(NM) $(LIBA)

lib_server:
		$(CC) -c $(SERVER_SRC)
		$(AR) $(SERVER_LIB) $(SERVER_OBJ)
		$(RL) $(SERVER_LIB)
		#$(NM) $(SERVER_LIB)

lib_jvlogger:
		$(CC) -c $(LOGGER_SRC)
		$(AR) $(LOGGER_LIB) $(LOGGER_OBJ)
		$(RL) $(LOGGER_LIB)
		#$(NM) $(LOGGER_LIB)

clean:
		rm *.o
