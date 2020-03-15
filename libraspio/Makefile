LIBDIR = lib/
LIBSRC = src/
OUT = bin/raspio

all:
	make -C $(LIBDIR)
	make -C $(LIBSRC)
	
run:
	$(OUT)

raspio:
		make -C $(LIBDIR) raspio
		make -C $(LIBSRC) raspio

reset:
	$(info cleaning the folder...)
	rm -f lib/*.a || :
	rm -f lib/*.o || :
	rm -f bin/*
	clear