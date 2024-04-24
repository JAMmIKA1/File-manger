#include "lotus.h"
#include <unistd.h>

void changePermissions(const char *path, unsigned int mode) {
    if (chmod(path, mode) == -1) {
        pcerror("\nError changing permissions");
    }
}
