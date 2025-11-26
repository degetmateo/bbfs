#ifndef BBFS_READ_H
#define BBFS_READ_H
#include <fuse3/fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "../read_file.h"

int bbfs_read (const char* path, char* buffer, size_t size, off_t offset, struct fuse_file_info* fi) {
    char filename[32];
    strcpy(filename, path);
    memmove(filename, filename + 1, strlen(filename));

    char* content = read_file(filename);
    if (!content) return -ENOENT;

    size_t len = strlen(content);

    if (offset >= len) {
        return 0;
    };

    if (offset + size > len) {
        size = len - offset;
    };

    memcpy(buffer, content + offset, size);
    return size;;
};

#endif