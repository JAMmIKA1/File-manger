#ifndef LOTUS_H
#define LOTUS_H

#include <dirent.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define BUFFSIZE 256
#define ST 2

void trim(char *input);
void parsePath(char *str);
void listFiles(const char *path, int show_hidden);
char *getFullPath(const char *path, char *name);
int isDir(const char *path);
void changePermissions(const char *path, unsigned int mode);
void makeDirectory(const char *path);
void deleteObject(const char *path);
void createSymbolicLink(char *src, const char *current_path);
char *getHome();
void pcerror(const char *err);

#endif
