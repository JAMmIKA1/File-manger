#include "lotus-cli.h"
#include "lotus.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
    // detect pathes in arguments
    if (argc > 1) {
        trim(argv[1]);
    }
	char *current_path = (argc >= 2 && isDir(argv[1])) ? getFullPath(0, argv[1])
													   : getSettedPath();
	char choice[1024], *next_path;
	int show_hidden = 0;

	while (1) {
		displayMenu(current_path, show_hidden);
		scanf("%s", choice);
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
			createSymbolicLink(next_path, current_path);
			free(next_path);
		} else if (!strcmp(choice, "mode")) {
			mode_t mode;
			scanf("%d", &mode);
			next_path = getNextPath(current_path);
			changePermissions(next_path, mode);
			free(next_path);
		} else if (!strcmp(choice, "hidden")) {
			show_hidden = !show_hidden;
		} else if (!strcmp(choice, "exit") || !strcmp(choice, "quit")) {
			return 0;
		} else if (!strcmp(choice, "help")) {
            displayHelpMenu();
        }
	}
}
