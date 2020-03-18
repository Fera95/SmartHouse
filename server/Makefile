SRC_DIR = src/
LIB_DIR = lib/
OUT_EXE = bin/main

all:
		mkdir -p bin && make -C $(LIB_DIR) && make -C $(SRC_DIR)

run:
		$(OUT_EXE)

clean:
	rm -r bin
	rm lib/*.o
	rm lib/*.a