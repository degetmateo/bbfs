#ifndef CHAIN_BLOCKS_H
#define CHAIN_BLOCKS_H

#include <stdio.h>

#include "fs.h"

int chain_blocks (int block_a_offset, int block_b_offset) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("chain_blocks: No se ha podido abrir el disco.");
        return -1;
    };

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Block block_a;
    fseek(disk, (sb.block_size * (sb.first_data_block_offset + block_a_offset)), SEEK_SET);
    fread(&block_a, sizeof(Block), 1, disk);

    block_a.next_block_offset = block_b_offset;

    fseek(disk, -sizeof(Block), SEEK_CUR);
    fwrite(&block_a, sizeof(Block), 1, disk);

    fclose(disk);
    return 0;
};

#endif