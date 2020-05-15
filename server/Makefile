SRC_DIR = src/
LIB_DIR = lib/
OUT_EXE = bin/SHServer2

all:
		$(info remember setting: ". /opt/poky/2.5.1/environment-setup-cortexa7hf-neon-vfpv4-poky-linux-gnueabi -c")
		make -C $(LIB_DIR) && make -C $(SRC_DIR)

run:
		$(info this makefile creates an ARM executable to run on a RaspberyPi)
		$(OUT_EXE)

clean:
	rm bin/SHserver2
	rm lib/*.a
	clear
