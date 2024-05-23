#pragma once

#include <unistd.h>

ssize_t FileGetSize(const char *path);
bool FileExists(const char *path);
int FileRead(const char *path, void *buffer, size_t size);

