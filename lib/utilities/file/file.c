#include <stdint.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "file.h"

ssize_t file_get_size(const char *path) {
	struct stat st = { 0 };
	if (stat(path, &st) != 0) {
		return -errno;
	}
	return st.st_size;
}

bool file_exists(const char *path) {
	struct stat st = { 0 };
	return stat(path, &st) ? false : true;
}

int file_read(const char *path, void *buffer, size_t size) {
	FILE *fp = fopen(path, "r");
	if (!fp) return -errno;
	if (fread(buffer, size, 1, fp) != size) {
		fclose(fp);
		return -errno;
	}
	fclose(fp);
	return 0;
}
