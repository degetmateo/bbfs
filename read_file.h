#ifndef READ_FILE_H
#define READ_FILE_H

#include <stdlib.h>
#include <string.h>

#include "fs.h"

char* read_file(char filename[32]) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("Error al abrir disco");
        return NULL;
    }

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Inode inode;
    fseek(disk, (sb.first_inode_block_offset * sb.block_size), SEEK_SET);

    unsigned int inode_number = 1;
    while (fread(&inode, sizeof(Inode), 1, disk) == 1) {
        if (inode_number > sb.total_inodes) {
            perror("read_file: No se ha encontrado el archivo.");
            fclose(disk);
            return NULL;
        }

        if (strcmp(filename, inode.filename) == 0) {
            break;
        };

        inode_number++;
    }

    char* result = NULL;
    unsigned long size = 0;  
    unsigned int actual_block_offset = inode.starting_block_offset;

    Block block;
    while (actual_block_offset != 0xFFFFFFFF) {
        fseek(disk, (sb.first_data_block_offset + actual_block_offset) * sb.block_size, SEEK_SET);
        if (fread(&block, sizeof(Block), 1, disk) != 1) {
            perror("Error al leer bloque");
            break;
        };

        unsigned long len = strnlen(block.data, sizeof(block.data));

        char* tmp = (char*) realloc(result, size + len + 1);
        if (!tmp) {
            free(result);
            fclose(disk);
            return NULL;
        }

        result = tmp;
        memcpy(result + size, block.data, len);
        size += len;
        result[size] = '\0';

        actual_block_offset = block.next_block_offset;
    }

    fclose(disk);
    return result;
}


#endif