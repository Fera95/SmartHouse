LIBDIR = lib/
LIBSRC = src/
OUT = bin/raspio

all:
	make -C $(LIBDIR)
	make -C $(LIBSRC)
	
run:
	$(OUT)

raspio:
		$(info "remember setting: . /opt/poky/2.5.1/environment-setup-cortexa7hf-neon-vfpv4-poky-linux-gnueabi -c")
		make -C $(LIBDIR)
		make -C $(LIBSRC)

reset:
	$(info cleaning the folder...)
	rm -f lib/*.a || :
	rm -f lib/*.o || :
	rm -f bin/*
	clear
