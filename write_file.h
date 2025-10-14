#ifndef WRITE_FILE_H
#define WRITE_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fs.h"

int clear_buffer () {
    int c;
    while ((c = getchar()) != '\n' && c!= EOF);
};

char* read_console () {
    clear_buffer();

    unsigned long reserved = 128;
    unsigned long size = 0;
    
    char* buffer = malloc(reserved);
    
    if (!buffer) return NULL;
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        buffer[size++] = c;
        
        if (size >= reserved - 1) {
            reserved *= 2;

            char* tmp = realloc(buffer, reserved);
            
            if (!tmp) {
                free(buffer);
                return NULL;
            }

            buffer = tmp;
        };
    };
    
    buffer[size] = '\0';
    return buffer;
};

int write_file () {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("write_file: Ha ocurrido un error.");
        return -1;
    };

    char filename[32];

    printf("Nombre del archivo: ");
    scanf("%32s", filename);

    printf("Escribe el archivo: ");
    char* data = read_console();

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

    while (block.next_block != 0) {
        fseek(disk, (sb.block_size * block.next_block), SEEK_CUR);
        fread(&block, sizeof(Block), 1, disk);
    };

    fseek(disk, -sizeof(Block), SEEK_CUR);

    // for (int i = 0; i < blocks_needed; i++) {
        memset(block.data, 0, sizeof(block.data));

        memcpy(block.data, data, 503);
        fwrite(&block, sizeof(Block), 1, disk);
        
        // break;
    // };

    free(data);
    fclose(disk);
    return 0;
};

#endif