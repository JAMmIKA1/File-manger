#include "lotus.h"

void pcerror(const char *err) {
	// custom error message
	char buff[BUFFSIZE] = "\x1b[1;31m";
	strcat(buff, err);
	perror(buff);
	printf("\x1b[0m");
	sleep(ST);
}
int isDir(const char *path) {
	DIR *dir;
	dir = opendir(path);
	if (dir == NULL) {
		return 0;
	}
	closedir(dir);
	return 1;
}

char *getFullPath(const char *path, char *name) {
	// concatenate two pathes with respect of special pathes ~ . .. /
	if (!name) {
		return 0;
	}
	trim(name);
	char *home = getHome();
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
	} else if (!strlen(name)) {
		asprintf(&fpath, "%s", home);
	} else if (name[0] == '~') {
		fpath = getFullPath(home, name + 2);
	} else if (name[0] == '/') {
		fpath = getFullPath(0, name);
	} else {
		asprintf(&fpath, "%s/%s", path, name);
	}
	parsePath(fpath);
	return fpath;
}
char *getNextPath(char *path) {
	char input[BUFFSIZE] = "";
	scanf("%[^\n]%*c", input);
	return getFullPath(path, input);
}
char *getHome() {
	struct passwd *pw = getpwuid(getuid());
	return pw->pw_dir;
}
