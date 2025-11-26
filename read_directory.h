#ifndef READ_DIRECTORY_H
#define READ_DIRECTORY_H

#include <stdio.h>
#include "fs.h"
#include "get_superblock.h"

int read_directory () {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("read_directory: Ha ocurrido un error.");
        return -1;
    };

    Superblock sb = get_superblock();

    Inode inode;
    fseek(disk, sb.first_inode_block_offset * sb.block_size, SEEK_SET);
    
    int inode_number = 1;
    while (fread(&inode, sizeof(Inode), 1, disk) == 1) {
        if (inode_number > sb.total_inodes) {
            break;
        };

        if (inode.is_used != 1) {
            inode_number++;
            continue;
        };

        printf("%s\n", inode.filename);
        inode_number++;
    };

    fclose(disk);
    return 0;
};

#endif