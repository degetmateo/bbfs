#ifndef FREE_CHAINED_BLOCKS_H
#define FREE_CHAINED_BLOCKS_H

#include <stdio.h>
#include <string.h>

#include "fs.h"
#include "free_block.h"

int free_chained_blocks (unsigned int block_offset) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("free_chained_blocks: Ha ocurrido un error.");
        return -1;
    };

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);    

    Block block;
    fseek(disk, (sb.first_data_block_offset + block_offset) * sb.block_size, SEEK_SET);
    fread(&block, sizeof(Block), 1, disk);

    unsigned int actual_block_offset = block.next_block_offset;

    block.next_block_offset = 0xFFFFFFFF;
    
    fseek(disk, -sizeof(Block), SEEK_CUR);
    fwrite(&block, sizeof(Block), 1, disk);

    while (actual_block_offset != 0xFFFFFFFF) {
        fseek(disk, (sb.first_data_block_offset + actual_block_offset) * sb.block_size, SEEK_SET);
        fread(&block, sizeof(Block), 1, disk);

        free_block(actual_block_offset);

        actual_block_offset = block.next_block_offset;
    };

    fclose(disk);
    return 0;
};

#endif