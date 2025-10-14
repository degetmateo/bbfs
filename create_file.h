#ifndef CREATE_FILE_H
#define CREATE_FILE_H

#include <stdio.h>
#include <string.h>

#include "fs.h"
#include "search_free_block.h"

int create_file () {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("create_file: Ha ocurrido un error.");
        return -1;
    };

    char filename[32];

    printf("Nombre del archivo: ");
    scanf("%32s", filename);

    Superblock sb;

    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    fseek(disk, (sb.starting_inode_block * sb.block_size), SEEK_SET);
    Inode inode;

    int inode_number = 1;
    while (fread(&inode, sizeof(Inode), 1, disk) == 1) {
        if (inode_number >= sb.total_inodes) {
            perror("create_file: No hay más Inodes libres.");
            fclose(disk);
            return -1;
        };

        if (!inode.is_used) {
            fseek(disk, -sizeof(Inode), SEEK_CUR);
            
            inode.is_used = 1;
            memcpy(inode.filename, filename, 32);

            fwrite(&inode, sizeof(Inode), 1, disk);
            break;
        };

        inode_number++;
    };

    Block block;
    fseek(disk, (sb.starting_data_block * sb.block_size), SEEK_SET);

    int block_number = 1;
    while (fread(&block, sizeof(Block), 1, disk) == 1) {
        if (block_number >= sb.total_blocks) {
            perror("create_file: No hay más bloques libres.");
            fclose(disk);
            return -1;
        };

        if (!block.is_used) {
            fseek(disk, -sizeof(Block), SEEK_CUR);
            
            block.is_used = 1;

            fwrite(&block, sizeof(Block), 1, disk);
            break;
        };

        block_number++;
    };

    fseek(disk, (((1 + inode_number) * sb.block_size)), SEEK_SET);
    fread(&inode, sizeof(Inode), 1, disk);
    fseek(disk, -sizeof(Inode), SEEK_CUR);

    inode.starting_block = block_number;

    fwrite(&inode, sizeof(Inode), 1, disk);

    fclose(disk);
    printf("Se ha creado un archivo con nombre: %32s", filename);
    return 0;
};

#endif