#include "fmheaders.h"

void createSymbolicLink(const char *src, const char *dst) {
    if (symlink(src, dst) == -1) {
        perror("Error creating symbolic link");
    }
}
