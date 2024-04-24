#include "lotus.h"

void changePermissions(const char *path, unsigned int mode) {
    if (chmod(path, mode) == -1) {
        perror("\nError changing permissions");
    }
}
