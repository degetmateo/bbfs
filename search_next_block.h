#ifndef SEARCH_NEXT_BLOCK_H
#define SEARCH_NEXT_BLOCK_H

#include <stdio.h>

#include "fs.h"
#include "search_free_block.h"
#include "chain_blocks.h"

int search_next_block (unsigned int block_number) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("search_next_block: Ha ocurrido un error.");
        return -1;
    };

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Block actual_block;
    fseek(disk, (sb.block_size * (sb.starting_data_block - 1 + block_number)), SEEK_SET);
    fread(&actual_block, sizeof(Block), 1, disk);

    unsigned int next_block_number;

    if (actual_block.next_block != 0) {
        next_block_number = actual_block.next_block;
    } else {
        next_block_number = search_free_block();
    };
    
    fclose(disk);
    return next_block_number;
};

#endif