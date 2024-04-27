#ifndef LOTUSCLI_H
#define LOTUSCLI_H

char *getSettedPath();
void displayMenu(const char *path, int show_hidden);
void displayHelpMenu();
char *getNextPath(const char *path);

#endif // !LOTUSCLI_H
