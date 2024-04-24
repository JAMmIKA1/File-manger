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
				} else {
                    perror("\nTask failed");
                }
				free(next_path);
				break;
            case '4':
                next_path = getNextPath(current_path);
                char dst[4096];
                printf("-> ");
                scanf("%[^\n]%*c", dst);
                createSymbolicLink(next_path, dst, current_path);
                free (next_path);
                break;
            case '5':
                next_path = getNextPath(current_path);
                int mode;
                scanf("%d%*c", &mode);
                changePermissions(next_path, mode);
				free(next_path);
				break;
			case '6':
				show_hidden = !show_hidden;
				break;
			default:
				return 0;
		}
	}
}
