#ifndef BBFS_OPEN_H
#define BBFS_OPEN_H

#include <fuse3/fuse.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "../fs.h"
#include "../open_disk.h"

int bbfs_open (const char* path, struct fuse_file_info* fi) {
    FILE *disk = open_disk();

    char filename[32];
    strcpy(filename, path);
    memmove(filename, filename + 1, strlen(filename));

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Inode inode;
    fseek(disk, sb.first_inode_block_offset * sb.block_size, SEEK_SET);

    unsigned int inode_number = 1;
    while (fread(&inode, sizeof(Inode), 1, disk) == 1) {
        if (inode_number > sb.total_inodes) {
            perror("bbfs_open: No se ha encontrado el archivo.");
            fclose(disk);
            return -ENOENT;
        };

        if (strcmp(inode.filename, filename) == 0) {
            break;
        };
    };

    fclose(disk);
    return 0;
};

#endif