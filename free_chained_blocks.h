#ifndef FREE_CHAINED_BLOCKS_H
#define FREE_CHAINED_BLOCKS_H

#include <stdio.h>
#include <string.h>

#include "fs.h"

int free_chained_blocks (unsigned int block_offset) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("free_chained_blocks: Ha ocurrido un error.");
        return -1;
    };

    Superblock superblock;
    fseek(disk, 0, SEEK_SET);
    fread(&superblock, sizeof(Superblock), 1, disk);

    Block block;
    fseek(disk, (superblock.first_data_block_offset + block_offset) * superblock.block_size, SEEK_SET);
    fread(&block, sizeof(Block), 1, disk);

    if (block.next_block_offset) {
        free_chained_blocks(block.next_block_offset);
    };

    block.is_used = 0;
    block.next_block_offset = 0;
    memset(block.data, 0, sizeof(block.data));
    
    fseek(disk, -sizeof(Block), SEEK_CUR);
    fwrite(&block, sizeof(Block), 1, disk);

    fclose(disk);
    return 0;
};

#endif