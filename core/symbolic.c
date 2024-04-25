#include "lotus.h"

void createSymbolicLink(char *src, const char *current_path) {
	char *dst = 0;
	size_t len = strlen(src);
	_Bool init = 0;

	// Split distance from source
	for (int i = 0; i < len - 1; i++) {
		if (src[i] == '-' && src[i + 1] == '>') {
			src[i] = 0;
			dst = src + i + 2;
		}
	}
	trim(src);
	trim(dst);
	if (!(*src && dst && *dst)) {
		puts("\x1b[1;31m\nError creating symbolic link: Missing "
			 "operand(s).\x1b[0m");
		sleep(ST);
		return;
	}
    dst = getFullPath(current_path, dst);

	if (symlink(src, dst) == -1) {
		pcerror("\nError creating symbolic link");
	}

	if (init) {
		free(dst);
	}
}
