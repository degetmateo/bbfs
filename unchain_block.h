#ifndef UNCHAIN_BLOCK_H
#define UNCHAIN_BLOCK_H

#include <stdio.h>

#include "fs.h"
#include "free_chained_blocks.h"

int unchain_block (unsigned int block_offset) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("unchain_block: Ha ocurrido un error.");
        return -1;
    };

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Block block;
    fseek(disk, (sb.first_data_block_offset + block_offset) * sb.block_size, SEEK_SET);
    fread(&block, sizeof(Block), 1, disk);
    
    free_chained_blocks(block.next_block_offset);

    block.next_block_offset = 0;

    fseek(disk, -sizeof(Block), SEEK_CUR);
    fwrite(&block, sizeof(Block), 1, disk);

    fclose(disk);
    return 0;
};

#endif