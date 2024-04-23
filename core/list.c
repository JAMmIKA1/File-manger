#include "fmheaders.h"

void listFiles(const char *path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, "..") && strcmp(entry->d_name, "."))
            printf("%s\n", entry->d_name);
    }

    closedir(dir);
}
