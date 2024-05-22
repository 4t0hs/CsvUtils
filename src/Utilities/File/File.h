#pragma once

#include <unistd.h>

typedef struct FileBuffer {
	char *data;
	size_t	size;
} FileBuffer_t;

ssize_t FileGetSize(const char *path);
bool FileExists(const char *path);
int FileRead(const char *path, void *buffer, size_t size);

