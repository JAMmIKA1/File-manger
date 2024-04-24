#ifndef LOTUSCLI_H
#define LOTUSCLI_H

char* getHome();
char* getSettedPath();
void displayMenu(const char* path, int show_hidden);
char* getNextPath(const char* path);

#endif // !LOTUSCLI_H
