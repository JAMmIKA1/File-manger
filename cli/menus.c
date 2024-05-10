#include "lotus-cli.h"
#include "lotus.h"

void displayMenu(const char *path, int show_hidden) {
	// ASNI text customization
	printf("\x1b[2J");
	printf("\x1b[H");
	printf("\x1b[1;32m~\x1b[0m> \x1b[1;97m%s\x1b[0m\n", path);
	puts("----------------------");
	listFiles(path, show_hidden);
	puts("\n----------------------");
	printf("\x1b[1;32m\\\x1b[0m> ");
}

void displayHelpMenu() {
	printf("\x1b[2J\x1b[H\x1b[1;97m");
	printf("Lotus Help Menu:\n");
	printf("-----------------------------------------------\n");
	printf("goto [DIRECTORY]\n"
		   "        \x1b[0;97mNavigate to another directory.\n\n");
	printf("\x1b[1;97mlink [SOURCE] -> [DEST]\n"
		   "        \x1b[0;97mMake symbolic link from SOURCE to DEST.\n\n");
	printf("\x1b[1;97mremove [ENTITY]\n"
		   "        \x1b[0;97mRemove directory or file.\n\n");
	printf("\x1b[1;97mmake [DIRECTORY_NAME]\n"
		   "        \x1b[0;97mCreate new directory.\n\n");
	printf("\x1b[1;97mmkfile [FILE_NAME]\n"
		   "        \x1b[0;97mCreate new file.\n\n");
	printf("\x1b[1;97mmode [PERMISSIONS_CODE] [ENTITY]\n"
		   "        \x1b[0;97mChange permissions for entity.\n\n");
	printf("\x1b[1;97mhidden\n"
		   "        \x1b[0;97mToggle hidden entities.\n\n");
	printf("\x1b[1;97mexit, quit\n"
		   "        \x1b[0;97mExit the file manager.\n\x1b[1;97m");
	printf("-----------------------------------------------\n");
	printf(":\x1b[0m");
	scanf("%*c%*s%*c");
}
