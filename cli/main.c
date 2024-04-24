#include "lotus.h"
#include "lotus-cli.h"

int main(int argc, char *argv[]) {
	char *current_path = getSettedPath();
	char choice, *next_path;
	int show_hidden = 0;

	while (1) {
        displayMenu(current_path, show_hidden);
		scanf("%c%*c", &choice);

		switch (choice) {
			case '1':
                next_path = getNextPath(current_path);
				makeDirectory(next_path);
				free(next_path);
				break;
			case '2':
                next_path = getNextPath(current_path);
				deleteObject(next_path);
				free(next_path);
				break;
			case '3':
                next_path = getNextPath(current_path);
				if (isDir(next_path)) {
					strcpy(current_path, next_path);
				}
				free(next_path);
				break;
			case '4':
				show_hidden = !show_hidden;
				break;
			default:
				return 0;
		}
	}
}
