#ifndef CHECK_CHAIN_H
#define CHECK_CHAIN_H

#include <stdio.h>
#include <string.h>
#include "fs.h"
#include "open_disk.h"

int check_chain (unsigned int prev_block_offset, unsigned int actual_block_offset) {
    FILE* disk = open_disk();

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Block prev_block;
    Block actual_block;

    fseek(disk, (sb.first_data_block_offset + prev_block_offset) * sb.block_size, SEEK_SET);
    fread(&prev_block, sizeof(Block), 1, disk);

    fseek(disk, (sb.first_data_block_offset + actual_block_offset) * sb.block_size, SEEK_SET);
    fread(&actual_block, sizeof(Block), 1, disk);

    if (memcmp(prev_block.hash, actual_block.prev_hash, 32) != 0) {
        fprintf(stderr, "\nERROR (check_chain): Bloque corrupto. PREV_HASH y HASH no coinciden.\n");
        return -1;
    };

    fclose(disk);
    return 0;
};

#endif