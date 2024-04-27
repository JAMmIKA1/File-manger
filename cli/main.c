#include "lotus-cli.h"
#include "lotus.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
	// detect pathes in arguments
	if (argc > 1) {
		trim(argv[1]);
	}
	char *pwd = (char *) malloc(BUFFSIZE);
	getcwd(pwd, BUFFSIZE);
	char *current_path = (argc >= 2 && isDir(argv[1]))
							 ? getFullPath(pwd, argv[1])
							 : getSettedPath();
	parsePath(current_path);
	free(pwd);
	char choice[BUFFSIZE], *next_path;
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
			char link_path[BUFFSIZE];
			next_path = getNextPath(current_path);
			ssize_t link_len =
				readlink(next_path, link_path, sizeof(link_path) - 1);
			link_path[link_len] = 0;
			char *lfpath = getFullPath(current_path, link_path);
			if (link_len != -1 && isDir(lfpath)) {
				strcpy(current_path, lfpath);
			} else if (isDir(next_path)) {
				strcpy(current_path, next_path);
			} else {
				pcerror("\nError open directory");
			}
			free(lfpath);
			free(next_path);
		} else if (!strcmp(choice, "link")) {
			next_path = (char *) malloc(BUFFSIZE * 2);
			scanf("%[^\n]%*c", next_path);
			createSymbolicLink(next_path, current_path);
			free(next_path);
		} else if (!strcmp(choice, "mode")) {
			mode_t mode;
			scanf("%o", &mode);
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
