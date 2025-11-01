#ifndef GET_INODE_OFFSET_H
#define GET_INODE_OFFSET_H

#include <stdio.h>
#include <string.h>
#include "fs.h"
#include "open_disk.h"
#include "get_superblock.h"

int get_inode_offset (char filename[32]) {
    FILE *disk = open_disk();

    if (!disk) {
        return -1;
    };

    Superblock sb = get_superblock();

    Inode inode;
    fseek(disk, (sb.first_inode_block_offset * sb.block_size), SEEK_SET);

    int inode_count = 1;
    int inode_offset = 0;
    while (fread(&inode, sizeof(Inode), 1, disk) == 1) {
        if (inode_count > sb.total_inodes) {
            perror("get_inode_offset: No se ha encontrado el Inode.");
            return -1;
        };

        if (strcmp(filename, inode.filename) == 0) {
            break;
        };
    };

    fclose(disk);
    return inode_offset;
};

#endif