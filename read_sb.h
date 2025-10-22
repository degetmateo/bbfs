#ifndef READ_SB_H
#define READ_SB_H

#include <stdio.h>
#include "fs.h"

int read_sb () {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("read_sb: Ha ocurrido un error.");
        return 1;
    };

    Superblock sb;

    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    fclose(disk);

    printf("name: %.4s\n", sb.name);
    printf("detail: %.4s\n", sb.detail);
    printf("total_blocks: %u\n", sb.total_blocks);
    printf("block_size: %u\n", sb.block_size);
    printf("block_data_size: %u\n", sb.block_data_size);
    printf("total_inodes: %u\n", sb.total_inodes);
    printf("inode_size: %u\n", sb.inode_size);
    printf("first_inode_block_offset: %u\n", sb.first_inode_block_offset);
    printf("first_data_block_offset: %u\n", sb.first_data_block_offset);

    return 0;
};

#endif