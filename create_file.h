#ifndef CREATE_FILE_H
#define CREATE_FILE_H

#include <stdio.h>
#include <string.h>

#include "fs.h"
#include "search_free_block.h"

int create_file (char filename[32]) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("create_file: Ha ocurrido un error.");
        return 1;
    };

    Superblock sb;

    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    fseek(disk, (sb.starting_inode_block * sb.block_size), SEEK_SET);
    Inode inode;

    int actual_inode = 1;
    while (fread(&inode, sizeof(Inode), 1, disk) == 1) {
        if (actual_inode >= sb.total_inodes) {
            perror("create_file: No hay más Inodes libres.");
            fclose(disk);
            return 1;
        };

        if (!inode.is_used) {
            fseek(disk, -sizeof(Inode), SEEK_CUR);
            
            inode.is_used = 1;
            memcpy(inode.filename, filename, 32);

            // BUSCAR Y ASIGNAR PRIMER BLOQUE

            fwrite(&inode, sizeof(Inode), 1, disk);
            break;
        };

        actual_inode++;
    };

    fclose(disk);

    printf("Se ha creado un archivo con nombre: %32s", filename);
    return 0;
};

#endif