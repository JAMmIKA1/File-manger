#include "lotus-cli.h"
#include "lotus.h"

int main(int argc, char *argv[]) {
	char *current_path = getSettedPath();
	char choice[5096], *next_path;
	int show_hidden = 0;

	while (1) {
		displayMenu(current_path, show_hidden);
		scanf("%s%*[\040]", choice);
		if (!strcmp(choice, "make")) {
			next_path = getNextPath(current_path);
			makeDirectory(next_path);
			free(next_path);
		} else if (!strcmp(choice, "remove")) {
			next_path = getNextPath(current_path);
			deleteObject(next_path);
			free(next_path);
		} else if (!strcmp(choice, "goto")) {
			next_path = getNextPath(current_path);
			if (isDir(next_path)) {
				strcpy(current_path, next_path);
			} else {
				pcerror("\nError open directory");
			}
			free(next_path);
		} else if (!strcmp(choice, "link")) {
			next_path = getNextPath(current_path);
			char *dst;
			printf("-> ");
            dst = getNextPath(0);
			createSymbolicLink(next_path, dst, current_path);
            free(dst);
			free(next_path);
		} else if (!strcmp(choice, "mode")) {
			int mode;
			scanf("%d%*[\040]", &mode);
			next_path = getNextPath(current_path);
			changePermissions(next_path, mode);
			free(next_path);
		} else if (!strcmp(choice, "hidden")) {
			show_hidden = !show_hidden;
		} else if (!strcmp(choice, "exit") || !strcmp(choice, "quit")) {
            return 0;
		}
	}
}
