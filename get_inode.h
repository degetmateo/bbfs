#ifndef GET_INODE_H
#define GET_INODE_H

#include <stdio.h>
#include <string.h>

#include "fs.h"

Inode get_inode (char filename[32]) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("get_inode: Ha ocurrido un error.");
        fclose(disk);
        return (Inode) { 0 };
    };

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Inode inode;
    fseek(disk, sb.first_inode_block_offset * sb.block_size, SEEK_SET);

    unsigned int inode_number = 1;
    while (fread(&inode, sizeof(Inode), 1, disk) == 1) {
        if (inode_number > sb.total_inodes) {
            perror("get_inode: Ha ocurrido un error.");
            fclose(disk);
            return (Inode) { 0 };
        };

        if (strcmp(inode.filename, filename) == 0) {
            break;
        };
    };

    fclose(disk);
    return inode;
};

#endif