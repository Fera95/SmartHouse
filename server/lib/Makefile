SERVER = libserver
SERVER_LIB = $(SERVER).a
SERVER_SRC = $(SERVER).c
SERVER_OBJ = $(SERVER).o

INC_DIR = ../include/
LIB_DIR=../lib/
CC = gcc -c -I$(INC_DIR)
AR = ar rvs

all: $(SERVER_LIB)

$(SERVER_LIB) : $(SERVER_OBJ)
		$(AR) $(SERVER_LIB) $(SERVER_OBJ)
$(SERVER_OBJ) : $(SERVER_SRC)
		$(CC) $(SERVER_SRC)

clean:
		rm *.o