#ifndef STACK_H
#define STACK_H
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/stat.h>

void listFiles(const char *path);
char *getFullPath(const char *path, const char *name);
void changePermissions(const char *path, unsigned int mode);
void makeDirectory(const char *path);
void deleteObject(const char *path);
void createSymbolicLink(const char *src, const char *dst);

#endif
