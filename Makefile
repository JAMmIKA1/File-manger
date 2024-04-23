CC="gcc"
flags="-g3"

build: ./*/*.c
	$(CC) ./*/*.c -o file_manager
debug: ./*/*.c
	$(CC) ./*/*.c $(flags) -o debug
