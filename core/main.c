#include "fmheaders.h"
#include <string.h>

int main(int argc, char *argv[]) {
	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	char *path = (char *) malloc(1024);
	path[0] = 0;
	path = getFullPath(path, homedir);
	char choice, str[BUFFSIZE], *fpath;
	int show_hidden = 0;

	while (1) {
		puts("\n----------------------");
		listFiles(path, show_hidden);
		puts("\n----------------------");
		printf("1. Make directory.\n2. Delete a file/directory.\n"
			   "3. Change directory.\n4. Toggle hidden files/directories.\n");
		printf("\n\\> ");
		scanf("%c%*c", &choice);
		switch (choice) {
			case '1':
				printf("> ");
				scanf("%[^\n]%*c", str);
				fpath = getFullPath(path, str);
				makeDirectory(fpath);
				free(fpath);
				break;
			case '2':
				printf("> ");
				scanf("%[^\n]%*c", str);
				fpath = getFullPath(path, str);
				deleteObject(fpath);
				free(fpath);
				break;
			case '3':
				printf("> ");
				scanf("%[^\n]%*c", str);
				fpath = getFullPath(path, str);
				if (isDir(fpath)) {
					strcpy(path, fpath);
				}
				free(fpath);
				break;
			case '4':
				show_hidden = !show_hidden;
				break;
			default:
				return 0;
		}
	}
}
