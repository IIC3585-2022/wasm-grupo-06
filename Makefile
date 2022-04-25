emcc:
	emcc -s ASSERTIONS=1 -s WASM=1 -s EXPORT_ES6=1 -s EXPORTED_RUNTIME_METHODS='["cwrap", "getValue", "setValue"]' -s EXPORTED_FUNCTIONS="['_partition', '_malloc']" -o Cpartition.js src/partition.c