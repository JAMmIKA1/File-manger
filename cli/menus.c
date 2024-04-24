#include "lotus-cli.h"
#include "lotus.h"

void displayMenu(const char *path, int show_hidden) {
	printf("\x1b[2J");
	printf("\x1b[H");
	printf("\x1b[1;32m~\x1b[0m> \x1b[1;97m%s\x1b[0m\n", path);
	puts("----------------------");
	listFiles(path, show_hidden);
	puts("\n----------------------");

	// printf("1. Make directory.\n2. Delete a file/directory.\n"
	// 	   "3. Change directory.\n4. Create symbolic link.\n"
	// 	   "5. Change permissions\n6. Toggle hidden files/directories.\n");

	printf("\\> ");
}

char *getNextPath(const char *path) {
	char input[BUFFSIZE];
	// printf(">> ");
	scanf("%[^\n]%*c", input);
    for (int i = strlen(input) - 1; i >= 0; i--) {
        if (input[i] != ' ') {
            input[i+1] = 0;
            break;
        }
    }
	return getFullPath(path, input);
}
