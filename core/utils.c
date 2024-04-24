#include "lotus.h"

int isDir(const char *path) {
	DIR *dir;
	dir = opendir(path);
	if (dir == NULL) {
		return 0;
	}
	closedir(dir);
	return 1;
}
char *getFullPath(const char *path, const char *name) {
	char *fpath;
	if (!path) {
		fpath = (char *) malloc(sizeof(char) * 4096);
		strcpy(fpath, name);
	} else if (!strcmp(name, "..")) {
		int i = strlen(path) - 1;
		asprintf(&fpath, "%s", path);
		while (i--) {
			if (fpath[i] == '/') {
				fpath[i ? i : i + 1] = 0;
				break;
			}
		}
	} else if (!strcmp(name, ".")) {
		asprintf(&fpath, "%s", path);
	} else if (strlen(path) == 1) {
		asprintf(&fpath, "%s%s", path, name);
	} else {
		asprintf(&fpath, "%s/%s", path, name);
	}
	return fpath;
}
char *getHome() {
	struct passwd *pw = getpwuid(getuid());
	return pw->pw_dir;
}
