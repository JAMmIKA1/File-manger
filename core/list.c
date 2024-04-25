#include "lotus.h"

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
    printf("\033[1;35m");
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == 4 && strcmp(entry->d_name, "..") &&
			strcmp(entry->d_name, ".") &&
			(show_hidden || entry->d_name[0] != '.')) {
			printf("%s/\n", entry->d_name);
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
            if (entry->d_type == 10) {
                printf("\033[1;36m");
            }
			printf("%s%c\033[0m\n", entry->d_name,
				   ((entry->d_type == 10) ? '@' : 0));
            files++;
		}
	}

    printf("\n%u directories, %u files", dirs, files);
	closedir(dir);
}
