#ifndef LOTUS_H
#define LOTUS_H

#include <pwd.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BUFFSIZE 255

void listFiles(const char *path, int show_hidden);
char *getFullPath(const char *path, const char *name);
int isDir(const char *path);
void changePermissions(const char *path, unsigned int mode);
void makeDirectory(const char *path);
void deleteObject(const char *path);
void createSymbolicLink(const char *src, const char *dst);

#endif
