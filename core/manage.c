#include "fmheaders.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void makeDirectory(const char *path) {
    if (mkdir(path, 0755) == -1) {
        perror("Error creating directory");
    }
}

void deleteObject(const char *path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir) {
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
        perror("Error deleting file");
    }
}
