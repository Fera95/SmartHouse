CC = gcc
#/opt/poky/2.5.1/environment-setup-cortexa7hf-neon-vfpv4-poky-linux-gnueabi
SRC = main.c

LIBNAME = libraspio
LIBA = ../lib/$(LIBNAME).a

OUT = ../bin/raspio

CFLAGS = -I../include
LDFLAGS = -L../lib 

#Create executables

executables:
		$(CC) -o $(OUT) $(SRC) $(CFLAGS) $(LDFLAGS) $(LIBA)
		$(info run "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib to finish the process")

raspio:
		$$CC -o $(OUT) $(SRC) $(CFLAGS) $(LDFLAGS) $(LIBA)
		
clean:
		rm $(OUT)