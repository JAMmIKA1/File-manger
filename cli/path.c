#include "lotus.h"
#include "lotus-cli.h"

char* getSettedPath() {
    const char* homedir = getHome();
    char *path = getFullPath(0, homedir);
    return path;
}
