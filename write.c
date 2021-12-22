#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	FILE *fd;
	char *buf, *blob;
	long bytes, size, addr;

	if ((fd = fopen("test", "rb")) == NULL) {
		fprintf(stderr, "error opening file [test rb]\n");
		exit(EXIT_FAILURE);
	}

	fseek(fd, 0, SEEK_END);
	bytes = ftell(fd);
	fseek(fd, 0, SEEK_SET);

	if ((buf = malloc(bytes)) == NULL) {
		fprintf(stderr, "error allocating memory [buf]\n");
		exit(EXIT_FAILURE);
	}

	fread(buf, 1, bytes, fd);

	if (fclose(fd) == EOF) {
		fprintf(stderr, "error closing file [test rb]\n");
		exit(EXIT_FAILURE);
	}

	if ((fd = fopen("blob", "rb")) == NULL) {
		fprintf(stderr, "error opening file [blob]\n");
		exit(EXIT_FAILURE);
	}

	fseek(fd, 0, SEEK_END);
	size = ftell(fd);
	fseek(fd, 0, SEEK_SET);

	if ((blob = malloc(size)) == NULL) {
		fprintf(stderr, "error allocating memory [blob]\n");
		exit(EXIT_FAILURE);
	}

	fread(blob, 1, size, fd);

	if (fclose(fd) == EOF) {
		fprintf(stderr, "error closing file [blob]\n");
		exit(EXIT_FAILURE);
	}

	for (size_t i = 0x1578; i < 0x1578+size; ++i) {
		buf[i] = blob[i-0x1578];
	} 

	free(blob);

	memcpy(&addr, buf+0x28, 8);
	memset(buf+0x28, 0, 8);
	memset(buf+0x3c, 0, 2);

	if ((fd = fopen("test", "wb")) == NULL) {
		fprintf(stderr, "error opening file [test wb]\n");
		exit(EXIT_FAILURE);
	}

	fwrite(buf, 1, addr, fd);

	if (fclose(fd) == EOF) {
		fprintf(stderr, "error closing file [test wb]\n");
		exit(EXIT_FAILURE);
	}

	free(buf);

	return EXIT_SUCCESS;
}
