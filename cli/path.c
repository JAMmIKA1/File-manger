#include "lotus-cli.h"
#include "lotus.h"

char *getSettedPath() {
	char *homedir = getHome();
	char *path = getFullPath(0, homedir);
	return path;
}
