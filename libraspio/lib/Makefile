CC = gcc -c
#CC = /opt/poky/2.5.1/environment-setup-cortexa7hf-neon-vfpv4-poky-linux-gnueabi -c
AR = ar rv
RL = ranlib
NM = nm -s
LD = ld -o

LIBNAME = libraspio
LIBSRC = $(LIBNAME).c
LIBA = $(LIBNAME).a
LIBSO = $(LIBNAME).so
LIBO = $(LIBNAME).o

# Create libraries

libraries:
		make static
		make clean

static:
		$(CC) $(LIBSRC)
		$(AR) $(LIBA) $(LIBO)
		$(RL) $(LIBA)
		#$(NM) $(LIBA)

raspio:
		$$CC -c libraspio.c
		$(AR) $(LIBA) $(LIBO)
		$(RL) $(LIBA)

clean:
		rm $(LIBO)