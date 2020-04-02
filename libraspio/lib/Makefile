#CC = gcc -c
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
		$(CC) -c $(LIBSRC)
		$(AR) $(LIBA) $(LIBO)
		$(RL) $(LIBA)
		$(NM) $(LIBA)

clean:
		rm $(LIBO)
