#ifndef CREATE_DISK_H
#define CREATE_DISK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fs.h"
#include "read_sb.h"

#define DISK_SIZE 5 * 1024 * 1024
#define BLOCK_SIZE 512
#define TOTAL_BLOCKS (DISK_SIZE / BLOCK_SIZE)
#define TOTAL_INODES 239
#define INODE_SIZE 512

int create_disk () {
    FILE *disk = fopen("disk.bbfs", "w+b");

    if (!disk) {
        perror("No se pudo crear el disco virtual.");
        return 1;
    };

    char empty_block[sizeof(Block)];
    memset(empty_block, 0, sizeof(Block));
    for (int i = 0; i < TOTAL_BLOCKS; i++) {
        fwrite(&empty_block, sizeof(Block), 1, disk);
    };
    
    Superblock sb;    
    
    memset(&sb, 0, sizeof(Superblock));
    memcpy(sb.name, "BBFS", 4);
    memcpy(sb.detail, "SOR2", 4);

    sb.total_blocks = TOTAL_BLOCKS;
    sb.block_size = BLOCK_SIZE;
    
    sb.total_inodes = TOTAL_INODES;
    sb.inode_size = INODE_SIZE;
    
    sb.starting_inode_block = 1;
    sb.starting_data_block = 1 + ((TOTAL_INODES * INODE_SIZE) / BLOCK_SIZE);

    fseek(disk, 0, SEEK_SET);
    fwrite(&sb, sizeof(Superblock), 1, disk);
    
    fclose(disk);

    printf("Disco virtual creado.\n");
    return 0;
};

#endif