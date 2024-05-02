#include "lotus.h"

void cutpart(char *str, size_t s, size_t e) {
	if (str && s >= 0 && e <= strlen(str) && e > s) {
		memcpy(str + s, str + e, strlen(str) - e + 1);
	}
};
void trim(char *input) {
	if (!input) {
		return;
	}
	long len = strlen(input), i, start = 0, end = 0;
	for (i = 0; i < len; i++) {
		if (!(input[i] == ' ' || input[i] == '\n')) {
			start = i;
			break;
		}
	}
	for (i = len - 1; i >= 0; i--) {
		if (!(input[i] == ' ' || input[i] == '\n' ||
			  (input[i] == '/' && i != start))) {
			end = i + 1;
			break;
		}
	}
	for (i = 0; start + i < end; i++) {
		input[i] = input[start + i];
	}
	if (start > end) {
		*input = 0;
	} else {
		input[end - start] = 0;
	}
}
void removeDuplicateSlashes(char *str) {
	for (int i = 0, j; str[i]; i++) {
		if (str[i] == '/') {
			for (j = i + 1; str[j]; j++) {
				if (str[j] != '/') {
					break;
				}
			}
			cutpart(str, i + 1, j);
		}
	}
}
void removeCurrentDot(char *str) {
	char *substr = "/./";
	size_t sublen = strlen(substr);
	while (1) {
		char *subaddr = strstr(str, substr);
		if (subaddr) {
			cutpart(str, subaddr - str, subaddr - str + sublen - 1);
		} else {
			break;
		}
	}
	size_t len = strlen(str);
	if (str[len - 1] == '.') {
		str[len - 1] = 0;
		len--;
	}
	// if (str[len - 1] == '/' && len > 1) {
	// 	str[len - 1] = 0;
	// }
}
void removeBackDots(char *str) {
	char *substr = "/../";
	size_t sublen = strlen(substr);
	while (1) {
		char *subaddr = strstr(str, substr);
		if (subaddr == str) {
			cutpart(str, 0, sublen - 1);
		} else if (subaddr) {
			size_t index = subaddr - str, i;
			for (i = index - 1; str[i] != '/'; i--)
				;
			cutpart(str, i, index + sublen - 1);
		} else {
			break;
		}
	}
	size_t len = strlen(str);
	if (str[len - 1] == '.') {
		str[len - 1] = 0;
		len--;
		if (len > 1) {
			int i;
			for (i = len - 2; str[i] != '/'; i--)
				;
			cutpart(str, i, len - 1);
		}
		len = strlen(str);
		if (len > 1) {
			str[len - 1] = 0;
		}
	}
}
void parsePath(char *str) {
	trim(str);
	removeDuplicateSlashes(str);
	removeCurrentDot(str);
	removeBackDots(str);
}
