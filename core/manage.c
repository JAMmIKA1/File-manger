#include "lotus.h"
char tmpbuff[BUFFSIZE];

void makeDirectory(const char *path) {
	if (mkdir(path, 0777) == -1) {
		pcerror("\nError creating directory");
	}
}

void deleteObject(const char *path) {
	DIR *dir = opendir(path);
	struct dirent *entry;
	ssize_t link_len = readlink(path, tmpbuff, sizeof(tmpbuff) - 1);

	// recursively delete all entities inside the directory
	if (dir && link_len == -1) {
		while ((entry = readdir(dir)) != NULL) {
			if (strcmp(entry->d_name, "..") && strcmp(entry->d_name, ".")) {
				char *fpath = getFullPath(path, entry->d_name);
				deleteObject(fpath);
				free(fpath);
			}
		}
		closedir(dir);
	}

	if (remove(path) == -1) {
		pcerror("\nError deleting file");
	}
}
