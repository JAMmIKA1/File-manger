#include "lotus.h"
#include "lotus-cli.h"

char *getHome() {
	struct passwd *pw = getpwuid(getuid());
	return pw->pw_dir;
}

char* getSettedPath() {
    const char* homedir = getHome();
    char *path = getFullPath(0, homedir);
    return path;
}
