#include "lotus.h"

void makeDirectory(const char *path) {
    if (mkdir(path, 0755) == -1) {
        pcerror("\nError creating directory");
    }
}

void deleteObject(const char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;

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
        pcerror("\nError deleting file");
    }
}
