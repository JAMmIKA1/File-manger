#include "fmheaders.h"

char *getFullPath(const char *path, const char *name);
int main(int argc, char *argv[]) {
	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	const char *path = homedir;
	char choice;

	while (1) {
        listFiles(path, 1);
        printf("\n> ");
		scanf("%c%*c", &choice);
        printf("> ");
		char str[BUFFSIZE], *fpath;
        scanf("%[^\n]%*c", str);
        fpath = getFullPath(path, str);
		switch (choice) {
			case '1':
                makeDirectory(fpath);
				break;
            case '2':
                deleteObject(fpath);
				break;
            default:
                return 0;
		}
        free(fpath);
	}
}
