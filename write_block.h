#ifndef WRITE_BLOCK_H
#define WRITE_BLOCK_H

#include <stdio.h>
#include <string.h>

#include "fs.h"

int write_block (unsigned int block_number, char* data, unsigned long size) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("write_block: Ha ocurrido un error.");
        return -1;
    };

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Block block;
    fseek(disk, (sb.block_size * (sb.starting_data_block + block_number)), SEEK_SET);
    
    if (size > sizeof(block.data)) size = sizeof(block.data);

    memset(block.data, 0, sizeof(block.data));
    memcpy(block.data, data, size);

    fwrite(&block, sizeof(Block), 1, disk);

    fclose(disk);
};

#endif