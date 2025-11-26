#ifndef WRITE_BLOCK_H
#define WRITE_BLOCK_H

#include <stdio.h>
#include <string.h>

#include "fs.h"
#include "sha256/hash.h"
#include "utils/print_bytes.h"
#include "get_block_hash.h"
#include "open_disk.h"

int write_block (unsigned int block_offset, char data[59], unsigned long size, int is_first, int prev_block_offset) {
    FILE *disk = open_disk();

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

        printf("is_first\n");
        // print_bytes(data, 59);
        // printf("is_first_genesis\n");
        // print_bytes(genesis, 32);
        
        hash((unsigned char*) block.data, genesis, prev_hash);

        // printf("is_first_prev_hash_result\n");
        // print_bytes(prev_hash, 32);

        memset(block.prev_hash, 0, sizeof(block.prev_hash));
        memcpy(block.prev_hash, prev_hash, sizeof(block.prev_hash));
    } else {
        if (prev_block_offset < 0) {
            perror("write_block: Ha ocurrido un error con el OFFSET del bloque.");
            return -1;
        };

        printf("is_not_first\n");

        printf("%d\n", prev_block_offset);

        unsigned char prev_hash[32]; 
        get_block_hash(prev_block_offset, prev_hash);

        printf("get_block_hash\n");
        print_bytes(prev_hash, 32);

        memset(block.prev_hash, 0, sizeof(block.prev_hash));
        memcpy(block.prev_hash, prev_hash, sizeof(block.prev_hash));
    };

    printf("prev hashes\n");
    print_bytes(block.prev_hash, 32);

    unsigned char block_hash[32];

    // printf("write_block\n\n");
    printf("HASH CREATION\n");
    printf("HASH CREATION DATA\n");
    print_bytes(block.data, 59);
    printf("HASH CREATION PREV_HASH\n");
    print_bytes(block.prev_hash, 32);

    hash((unsigned char*) block.data, block.prev_hash, block_hash);
    
    // printf("block_hash_result\n");
    // print_bytes(block_hash, 32);

    memset(block.hash, 0, sizeof(block.hash));
    memcpy(block.hash, block_hash, sizeof(block.hash));

    printf("TEST 1");

    fseek(disk, -sizeof(Block), SEEK_CUR);
    fwrite(&block, sizeof(Block), 1, disk);

    printf("TEST 2");

    fclose(disk);
    return 0;
};

#endif