#ifndef WRITE_BLOCK_H
#define WRITE_BLOCK_H

#include <stdio.h>
#include <string.h>

#include "fs.h"
#include "sha256/hash.h"

int write_block (unsigned int block_offset, char data[59], unsigned long size, int is_first) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("write_block: Ha ocurrido un error.");
        return -1;
    };

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Block block;
    fseek(disk, (sb.block_size * (sb.first_data_block_offset + block_offset)), SEEK_SET);
    fread(&block, sizeof(Block), 1, disk);

    memset(block.data, 0, sizeof(block.data));
    memcpy(block.data, data, size);

    if (is_first) {
        unsigned char prev_hash[32];
        unsigned char genesis[32] = "SOR2_TP_FINAL";

        hash((unsigned char*) data, genesis, prev_hash);

        memset(block.prev_hash, 0, sizeof(block.prev_hash));
        memcpy(block.prev_hash, prev_hash, sizeof(block.prev_hash));
    };

    unsigned char block_hash[32];

    hash((unsigned char*) data, block.prev_hash, block_hash);
    
    memset(block.hash, 0, sizeof(block.hash));
    memcpy(block.hash, block_hash, sizeof(block.hash));

    fseek(disk, -sizeof(Block), SEEK_CUR);
    fwrite(&block, sizeof(Block), 1, disk);

    fclose(disk);
    return 0;
};

#endif