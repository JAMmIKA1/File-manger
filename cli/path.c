#include "lotus.h"
#include "lotus-cli.h"

char* getSettedPath() {
    char* homedir = getHome();
    char *path = getFullPath(0, homedir);
    return path;
}
