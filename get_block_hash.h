#ifndef GET_BLOCK_HASH_H
#define GET_BLOCK_HASH_H

#include <stdio.h>
#include <string.h>

#include "fs.h"

int get_block_hash (int block_offset, unsigned char buffer[32]) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("get_block_hash: Ha ocurrido un error.");
        return -1;
    };

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Block block;
    fseek(disk, (sb.first_data_block_offset + block_offset) * sb.block_size, SEEK_SET);
    fread(&block, sizeof(Block), 1, disk);

    memset(buffer, 0, 32);
    memcpy(buffer, block.hash, 32);
};

#endif