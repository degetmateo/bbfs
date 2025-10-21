#ifndef SEARCH_FREE_BLOCK_H
#define SEARCH_FREE_BLOCK_H

#include <stdio.h>

#include "fs.h"

int search_free_block () {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("search_free_block: Ha ocurrido un error.");
        return -1;
    };

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Block block;
    fseek(disk, ((sb.starting_data_block - 1) * sb.block_size), SEEK_SET);
    
    int block_number = 1;
    while (fread(&block, sizeof(Block), 1, disk) == 1) {
        if (!block.is_used) {
            fseek(disk, -sizeof(Block), SEEK_CUR);

            block.is_used = 1;
            
            fwrite(&block, sizeof(Block), 1, disk);
            break;
        };

        block_number++;
    };

    fclose(disk);
    return block_number;
};

#endif