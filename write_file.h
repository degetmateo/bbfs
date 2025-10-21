#ifndef WRITE_FILE_H
#define WRITE_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fs.h"
#include "./utils/read_console.h"
#include "write_block.h"
#include "chain_blocks.h"
#include "search_next_block.h"

int write_file (char filename[32], Buffer buffer) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("write_file: Ha ocurrido un error.");
        return -1;
    };

    Superblock sb;

    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Inode inode;
    fseek(disk, (sb.block_size * (sb.starting_inode_block - 1)), SEEK_SET);

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

    int actual_block_number = inode.starting_block;
    unsigned long offset = 0;

    while (offset < buffer.size) {
        unsigned long remaining = buffer.size - offset;
        unsigned long to_write = (remaining > sb.block_data_size) ? sb.block_data_size : remaining;

        if (write_block(actual_block_number, buffer.data + offset, to_write) == -1) {
            perror("write_file: Ha ocurrido un error al escribir el archivo.");
            free(buffer.data);
            fclose(disk);
            return -1;
        };
        
        int next_block_number = search_next_block(actual_block_number);
        
        if (next_block_number == -1) {
            perror("write_file: No hay bloques disponibles.");
            free(buffer.data);
            fclose(disk);
            return -1;
        };
        
        chain_blocks(actual_block_number, next_block_number);
        
        actual_block_number = next_block_number;
        offset = offset + to_write;
    };

    free(buffer.data);
    fclose(disk);
    return 0;
};

#endif