SRC_DIR = src/
LIB_DIR = lib/
OUT_EXE = bin/main

all:
		$(info remember setting: ". /opt/poky/2.5.1/environment-setup-cortexa7hf-neon-vfpv4-poky-linux-gnueabi -c")
		mkdir -p bin && make -C $(LIB_DIR) && make -C $(SRC_DIR)

run:
		$(OUT_EXE)

clean:
	rm -r bin
	rm lib/*.o
	rm lib/*.a
	clear