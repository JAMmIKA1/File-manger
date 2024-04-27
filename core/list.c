#include "lotus.h"
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>

void printFile(char *d_name, unsigned char d_type, const char *path) {
	ssize_t link_len = -1;
	char specialchar = 0;
	struct stat fileStat;
	char link_path[BUFFSIZE];
	char *fpath = getFullPath(path, d_name);
	stat(fpath, &fileStat);
	if (d_type == 10) {
		link_len = readlink(fpath, link_path, sizeof(link_path) - 1);
		link_path[link_len] = 0;
		printf("\033[1;36m");
		specialchar = '@';
	} else {
		if (!isDir(fpath) &&
			(fileStat.st_mode & S_IXUSR || fileStat.st_mode & S_IXGRP ||
			 fileStat.st_mode & S_IXOTH)) {
			printf("\033[1;32m");
			specialchar = '*';
		}
	}
	printf("%s\033[0m%c", d_name, specialchar);
	if (link_len != -1) {
		char *lfpath = getFullPath(path, link_path);
		printf(" -> ");
		if (isDir(lfpath)) {
			printf("\033[1;35m%s\033[0m/", lfpath);
		} else {
			printFile(lfpath, 0, 0);
		}
	}
}
void listFiles(const char *path, int show_hidden) {
	DIR *dir;
	struct dirent *entry;
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
		if (entry->d_type != 4 && strcmp(entry->d_name, "..") &&
			strcmp(entry->d_name, ".") &&
			(show_hidden || entry->d_name[0] != '.')) {
			printFile(entry->d_name, entry->d_type, path);
			putchar('\n');
			files++;
		}
	}

	printf("\n%u directories, %u files", dirs, files);
	closedir(dir);
}
