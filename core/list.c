#include "lotus.h"

void listFiles(const char *path, int show_hidden) {
	DIR *dir;
	struct dirent *entry;

	dir = opendir(path);
	if (dir == NULL) {
		perror("\nError opening directory");
		return;
	}

	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, "..") && strcmp(entry->d_name, ".") &&
			(show_hidden || entry->d_name[0] != '.')) {
			printf("%s\n", entry->d_name);
		}
	}
	closedir(dir);
}
