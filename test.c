#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH_LEN 0x50
#define LINE_LEN 0x100
#define NAME_LEN 0x14

int main(void) {
	FILE *fd;
	pid_t pid;
	char path[PATH_LEN+1];
	char line[LINE_LEN+1];
	char name[NAME_LEN+1];
	int i;
	char ch;
	long addr;
	void (*func)(char *,int);

	pid = getpid();
	snprintf(path, PATH_LEN, "/proc/%d/maps", pid);

	if ((fd = fopen(path, "rb")) == NULL) {
		fprintf(stderr, "error opening file [%s]\n", path);
		exit(EXIT_FAILURE);
	}

	i = 0;

	while (1) {
		if ((ch = fgetc(fd)) == EOF) {
			break;
		}

		if (ch == 0x0a) {
			line[i] = 0;
			i = -1;
			
			if (strstr(line, "/test")) {
				break;
			}
		}

		line[i] = ch;
		++i;
	}

	if (fclose(fd) == EOF) {
		fprintf(stderr, "error closing file [%s]\n", path);
		exit(EXIT_FAILURE);
	}

	line[0xc] = 0;
	addr = strtol(line, NULL, 16);
	addr += 0x1578;

	printf("Enter your name: ");
	fgets(name, NAME_LEN, stdin);

	func = (void (*)(char *,int)) addr;
	func(name, strlen(name));

	return EXIT_SUCCESS;
}
