SERVER_LIB = libserver.a
SERVER_SRC = libserver.c
SERVER_OBJ = libserver.o

ARDUINOCOMMS_LIB = libarduinocomms.a
ARDUINOCOMMS_SRC = libarduinocomms.c
ARDUINOCOMMS_OBJ = libarduinocomms.o

INC_DIR = ../include/
LIB_DIR=../lib/
CC = gcc -c -I$(INC_DIR)
AR = ar rvs

all: $(SERVER_LIB) $(ARDUINOCOMMS_LIB)

$(ARDUINOCOMMS_LIB) : $(ARDUINOCOMMS_OBJ)
		$(AR) $(ARDUINOCOMMS_LIB) $(ARDUINOCOMMS_OBJ)
$(ARDUINOCOMMS_OBJ) : $(ARDUINOCOMMS_SRC)
		$(CC) $(ARDUINOCOMMS_SRC)

$(SERVER_LIB) : $(SERVER_OBJ)
		$(AR) $(SERVER_LIB) $(SERVER_OBJ)
$(SERVER_OBJ) : $(SERVER_SRC)
		$(CC) $(SERVER_SRC)



clean:
		rm *.o