#ifndef READ_BLOCK_H
#define READ_BLOCK_H

#include <stdio.h>

#include "fs.h"

Block read_block (unsigned int block_number) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("read_block: Ha ocurrido un error.");
        return (Block){0, 0, {""}};
    };

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Block block;
    fseek(disk, (sb.block_size * (sb.starting_data_block - 1 + block_number)), SEEK_SET);
    fread(&block, sizeof(Block), 1, disk);

    fclose(disk);
    return block;
};

#endif