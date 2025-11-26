#ifndef GET_INODE_H
#define GET_INODE_H

#include <stdio.h>
#include <string.h>

#include "fs.h"
#include "open_disk.h"

int get_inode (char filename[32], Inode* dest) {
    FILE *disk = open_disk();

    if (!disk) {
        perror("get_inode: Ha ocurrido un error.");
        fclose(disk);
        return -ENOENT;
    };

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    fseek(disk, sb.first_inode_block_offset * sb.block_size, SEEK_SET);

    unsigned int inode_number = 1;
    while (fread(dest, sizeof(Inode), 1, disk) == 1) {
        if (inode_number > sb.total_inodes) {
            perror("get_inode: Ha ocurrido un error.");
            fclose(disk);
            return -ENOENT;
        };

        if (strcmp(dest->filename, filename) == 0) {
            break;
        };
    };

    fclose(disk);
    return 0;
};

#endif