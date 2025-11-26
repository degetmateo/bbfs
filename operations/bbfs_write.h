#ifndef BBFS_WRITE_H
#define BBFS_WRITE_H

#include <fuse3/fuse.h>
#include <stdio.h>

#include "../fs.h"
#include "../get_inode.h"
#include "../write_file.h"

int bbfs_write (const char* path, const char* buf, size_t size, off_t offset, struct fuse_file_info* fi) {
    (void) offset;
    
    printf("%s", path);

    Buffer buffer;
    memcpy(buffer.data, buf, sizeof(buf));
    buffer.size = size;

    const char *filename = path + 1;
    if (write_file(filename, buffer) != 0) {
        printf("TEST");
        return -ENOENT;
    };

    return size;
};

#endif