#include "lotus.h"

void changePermissions(const char *path, mode_t mode) {
	if (chmod(path, mode) == -1) {
		pcerror("\nError changing permissions");
	}
}
