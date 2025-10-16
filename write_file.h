#ifndef WRITE_FILE_H
#define WRITE_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fs.h"
#include "./utils/read_console.h"

int write_file (char filename[32], char* data) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("write_file: Ha ocurrido un error.");
        return -1;
    };

    Superblock sb;

    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Inode inode;
    fseek(disk, (sb.block_size * sb.starting_inode_block), SEEK_SET);

    unsigned int inode_number = 1;
    while (fread(&inode, sizeof(Inode), 1, disk) == 1) {
        if (inode_number > sb.total_inodes) {
            perror("write_file: No se ha encontrado el archivo.");
            return -1;
        };

        if (strcmp(filename, inode.filename) == 0) {
            break;
        };

        inode_number++;
    };

    unsigned int blocks_needed = (sizeof(data) + 503 - 1) / 503;

    if (blocks_needed > sb.total_blocks) {
        perror("write_file: No hay tantos bloques!");
        return -1;
    };
    
    Block block;
    fseek(disk, (sb.block_size * (sb.starting_data_block + inode.starting_block)), SEEK_SET);
    fread(&block, sizeof(Block), 1, disk);

    // while (block.next_block != 0) {
    //     fseek(disk, (sb.block_size * block.next_block), SEEK_CUR);
    //     fread(&block, sizeof(Block), 1, disk);
    // };

    fseek(disk, -sizeof(Block), SEEK_CUR);

    unsigned long offset = 0;

    while (offset < sizeof(data)) {
        unsigned long remaining = sizeof(data) - offset;
        unsigned long to_write = (remaining > sb.block_size) ? sb.block_size : remaining;

        unsigned int free_block_number = search_free_block();
        
        if (free_block_number == -1) {
            perror("write_file: No hay bloques disponibles.");
            return -1;
        };

        
    };

    // for (int i = 0; i < blocks_needed; i++) {
    //     memset(block.data, 0, sizeof(block.data));

    //     memcpy(block.data, data, 503);
    //     fwrite(&block, sizeof(Block), 1, disk);
        
    //     break;
    // };

    free(data);
    fclose(disk);
    return 0;
};

#endif