#ifndef CHAIN_BLOCKS_H
#define CHAIN_BLOCKS_H

#include <stdio.h>

#include "fs.h"

int chain_blocks (int a, int b) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("chain_blocks: No se ha podido abrir el disco.");
        return -1;
    };

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Block block_a;
    fseek(disk, (sb.block_size * (sb.starting_data_block + a)), SEEK_SET);
    fread(&block_a, sizeof(Block), 1, disk);
    
    block_a.is_used = 1;
    block_a.next_block = b;

    fseek(disk, -sizeof(Block), SEEK_CUR);
    fwrite(&block_a, sizeof(Block), 1, disk);

    Block block_b;
    fseek(disk, (sb.block_size * (sb.starting_data_block + b)), SEEK_SET);
    fread(&block_b, sizeof(Block), 1, disk);

    block_b.is_used = 1;
    block_b.previous_block = a;

    fseek(disk, -sizeof(Block), SEEK_CUR);
    fwrite(&block_b, sizeof(Block), 1, disk);

    fclose(disk);
};

#endif