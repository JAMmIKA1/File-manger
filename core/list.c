#include "lotus.h"
#include <stdio.h>

void listFiles(const char *path, int show_hidden) {
	DIR *dir;
	struct dirent *entry;
	struct stat fileStat;
	char fpath[4096];
	unsigned dirs = 0, files = 0;

	dir = opendir(path);
	if (dir == NULL) {
		pcerror("\nError opening directory");
		return;
	}

	// Print directories first
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == 4 && strcmp(entry->d_name, "..") &&
			strcmp(entry->d_name, ".") &&
			(show_hidden || entry->d_name[0] != '.')) {
			printf("\033[1;35m%s\033[0m/\n", entry->d_name);
			dirs++;
		}
	}

	// Print files
	printf("\033[0m");
	rewinddir(dir);

	while ((entry = readdir(dir)) != NULL) {
		char specialchar = 0;
		if (entry->d_type != 4 && strcmp(entry->d_name, "..") &&
			strcmp(entry->d_name, ".") &&
			(show_hidden || entry->d_name[0] != '.')) {
			snprintf(fpath, 4096, "%s/%s", path, entry->d_name);
			stat(fpath, &fileStat);
			if (entry->d_type == 10) {
				printf("\033[1;36m");
				specialchar = '@';
			} else {
				if (fileStat.st_mode & S_IXUSR || fileStat.st_mode & S_IXGRP ||
					fileStat.st_mode & S_IXOTH) {
					printf("\033[1;32m");
					specialchar = '*';
				}
			}
			printf("%s\033[0m%c\n", entry->d_name, specialchar);
			files++;
		}
	}

	printf("\n%u directories, %u files", dirs, files);
	closedir(dir);
}
