#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAXELEMENTS 65535
#define BUFFSIZE 255

typedef struct object {
	char name[BUFFSIZE];
	char size[10];
	_Bool isDir;
} object;

int isDirectory(object *obj, const char *path);
char *getObjectSize(object *obj, const char *path);
object **getObjects(const char *path);
void destroyObjects(object **list);

int main(int argc, char *argv[]) {
	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	const char *path = argv[1];

	object **obj = getObjects(path);

	for (int i = 0; obj[i]; i++) {
		printf("%s %s %d\n", getObjectSize(obj[i], path), obj[i]->name,
			   isDirectory(obj[i], path));
	}
	destroyObjects(obj);
}

int isDirectory(object *obj, const char *path) {
	char *full_path;
	asprintf(&full_path, "%s/%s", path, obj->name);
	struct stat statbuf;
	if (stat(full_path, &statbuf) != 0)
		return 0;
	obj->isDir = S_ISDIR(statbuf.st_mode);
	return obj->isDir;
}

char *getObjectSize(object *obj, const char *path) {
	char cmd[1024];
	snprintf(cmd, 1024, "du -ch %s/%s | grep total | awk '{print $1;}'", path,
			 obj->name);

	FILE *fp = popen(cmd, "r");
	fgets(obj->size, sizeof(obj->size), fp);
	fclose(fp);
	obj->size[strlen(obj->size) - 1] = 0;
	return obj->size;
}
object **getObjects(const char *path) {
	char cmd[1024] = "ls -b ";
	strcat(cmd, path);
	FILE *fp = popen(cmd, "r");
	object **obj = (object **) malloc(sizeof(object *) * MAXELEMENTS);
	int numOfObjects;

	for (numOfObjects = 0;; numOfObjects++) {
		obj[numOfObjects] = (object *) malloc(sizeof(object));
		if (!fgets(obj[numOfObjects]->name, BUFFSIZE, fp)) {
			free(obj[numOfObjects]);
			obj[numOfObjects] = 0x0;
			break;
		}
		obj[numOfObjects]->name[strlen(obj[numOfObjects]->name) - 1] = 0;
	}
	return obj;
}
void destroyObjects(object **list) {
	for (int i = 0; list[i]; i++) {
		free(list[i]);
	}
	free(list);
}
