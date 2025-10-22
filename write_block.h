#ifndef WRITE_BLOCK_H
#define WRITE_BLOCK_H

#include <stdio.h>
#include <string.h>

#include "fs.h"

int write_block (unsigned int block_offset, char* data, unsigned long size) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("write_block: Ha ocurrido un error.");
        return -1;
    };

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Block block;
    fseek(disk, (sb.block_size * (sb.first_data_block_offset + block_offset)), SEEK_SET);
    fread(&block, sizeof(Block), 1, disk);

    memset(block.data, 0, sizeof(block.data));
    memcpy(block.data, data, size);

    fseek(disk, -sizeof(Block), SEEK_CUR);
    fwrite(&block, sizeof(Block), 1, disk);

    fclose(disk);
    return 0;
};

#endif