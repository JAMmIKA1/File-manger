#include "lotus.h"

void createSymbolicLink(const char *src, char *dst, const char *current_path) {
	char *home = getHome();
	if (dst[0] == '~') {
		dst = getFullPath(home, dst + 1);
	} else if (dst[0] != '/') {
		dst = getFullPath(current_path, dst);
	}
	if (symlink(src, dst) == -1) {
        pcerror("\nError creating symbolic link");
	}
	if (dst[0] != '/') {
		free(dst);
	}
}
