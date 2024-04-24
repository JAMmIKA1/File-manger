CC="gcc"
flags="-g3"

lotus: ./*/*.c
	$(CC) ./*/*.c -o lotus
debug: ./*/*.c
	$(CC) ./*/*.c $(flags) -o debug
