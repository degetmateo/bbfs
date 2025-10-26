#ifndef FREE_BLOCK_H
#define FREE_BLOCK_H

#include <stdio.h>
#include "fs.h"

int free_block (unsigned int block_offset) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("free_block: Ha ocurrido un error.");
        return -1;
    };

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Block block;
    fseek(disk, (sb.first_data_block_offset + block_offset) * sb.block_size, SEEK_SET);
    fread(&block, sizeof(Block), 1, disk);

    block.is_used = 0;
    block.next_block_offset = 0xFFFFFFFF;

    fseek(disk, -sizeof(Block), SEEK_CUR);
    fwrite(&block, sizeof(Block), 1, disk);

    fclose(disk);
    return 0;
};

#endif