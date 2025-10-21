#ifndef CHAIN_BLOCKS_H
#define CHAIN_BLOCKS_H

#include <stdio.h>

#include "fs.h"

int chain_blocks (int block_a_number, int block_b_number) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("chain_blocks: No se ha podido abrir el disco.");
        return -1;
    };

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Block block_a;
    fseek(disk, (sb.block_size * (sb.starting_data_block - 1 + block_a_number)), SEEK_SET);
    fread(&block_a, sizeof(Block), 1, disk);

    block_a.next_block = block_b_number;

    fseek(disk, -sizeof(Block), SEEK_CUR);
    fwrite(&block_a, sizeof(Block), 1, disk);

    fclose(disk);
    return 0;
};

#endif