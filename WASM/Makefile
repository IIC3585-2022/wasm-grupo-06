
EMCC=emcc

all: partition.cpp
	$(EMCC) -O3 -s WASM=1 -o partitionWASM.js -s EXPORTED_FUNCTIONS="['_partition']" -s EXPORT_ES6=1 -s MODULARIZE=1 partition.cpp