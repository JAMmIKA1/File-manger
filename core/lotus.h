#ifndef LOTUS_H
#define LOTUS_H
#define BUFFSIZE 4096
#define ST 2

#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void listFiles(const char *path, int show_hidden);
void changePermissions(const char *path, unsigned int mode);
void makeDirectory(const char *path);
void deleteObject(const char *path);
void createSymbolicLink(char *src, const char *current_path);

char *getFullPath(const char *path, char *name);
char *getNextPath(char *path);
char *getSettedPath();
char *getHome();

void trim(char *input);
void pcerror(const char *err);
void parsePath(char *str);
int isDir(const char *path);

#endif
