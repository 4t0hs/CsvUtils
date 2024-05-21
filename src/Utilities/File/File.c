#include <stdint.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "File.h"

 ssize_t FileGetSize(const char *path) {
	struct stat st = {0};
	if (stat(path, &st) != 0) {
		return -errno;
	}
	return st.st_size;
}

bool FileExists(const char *path) {
	struct stat st = {0};
	return stat(path, &st) ? false : true;
}

int FileRead(const char *path, FileBuffer_t *buffer) {
	int64_t size = FileGetSize(path);
	if (size < 0) {
		return size;
	}
	buffer->data = (char *)malloc(size);
	if (!buffer->data) {
		return -errno;
	}
	FILE *fp = fopen(path, "r");
	if (!fp) return -errno;
	if (fread(buffer->data, size, 1, fp) != size) {
		free(buffer->data);
		fclose(fp);
		return -errno;
	}
	fclose(fp);
	buffer->size = size;
	return 0;
}

size_t FileCountLine(const char *data, const char *eolChar) {
	size_t counter = 1;	// 最低でも1行はあるので初期値は1
	char *p = NULL;
	while ((p = strstr(data, eolChar)) != NULL) {
		data = p;
		counter++;
	}
	return counter;
}
