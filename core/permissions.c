#include "lotus.h"

void changePermissions(const char *path, unsigned int mode) {
    if (chmod(path, mode) == -1) {
        perror("Error changing permissions");
    }
}
