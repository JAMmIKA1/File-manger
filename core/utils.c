#include "fmheaders.h"

char *getFullPath(const char *path, const char *name) {
	char *fpath;
	asprintf(&fpath, "%s/%s", path, name);
	return fpath;
}
