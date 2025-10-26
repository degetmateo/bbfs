#ifndef SEARCH_NEXT_BLOCK_H
#define SEARCH_NEXT_BLOCK_H

#include <stdio.h>

#include "fs.h"
#include "search_free_block.h"
#include "chain_blocks.h"

int search_next_block (unsigned int block_offset) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("search_next_block: Ha ocurrido un error.");
        return -1;
    };

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Block actual_block;
    fseek(disk, (sb.block_size * (sb.first_data_block_offset + block_offset)), SEEK_SET);
    fread(&actual_block, sizeof(Block), 1, disk);

    unsigned int next_block_offset;

    if (actual_block.next_block_offset != 0xFFFFFFFF) {
        next_block_offset = actual_block.next_block_offset;
    } else {
        next_block_offset = search_free_block();
    };
    
    fclose(disk);
    return next_block_offset;
};

#endif