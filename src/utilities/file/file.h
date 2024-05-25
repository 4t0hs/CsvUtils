#pragma once

#include <unistd.h>
#include <stdbool.h>

ssize_t file_get_size(const char *path);
bool file_exists(const char *path);
int file_read(const char *path, void *buffer, size_t size);

