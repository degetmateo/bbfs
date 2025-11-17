#ifndef CREATE_FILE_H
#define CREATE_FILE_H

#include <stdio.h>
#include <string.h>

#include "fs.h"
#include "search_free_block.h"

int create_file (char filename[32]) {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        fprintf(stderr, "\nERROR (create_file): Ha ocurrido un error al abrir el disco.\n");
        return -1;
    };

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Inode inode;
    fseek(disk, (sb.first_inode_block_offset * sb.block_size), SEEK_SET);

    int inode_number = 1;
    while (fread(&inode, sizeof(Inode), 1, disk) == 1) {
        if (inode_number > sb.total_inodes) {
            fprintf(stderr, "\nERROR (create_file): No hay más Inodes libres.\n");
            fclose(disk);
            return -1;
        };

        if (!inode.is_used) {
            fseek(disk, -sizeof(Inode), SEEK_CUR);
            
            inode.is_used = 1;
            memset(inode.filename, 0, sizeof(inode.filename));
            memcpy(inode.filename, filename, 32);
            inode.starting_block_offset = search_free_block();
            
            fwrite(&inode, sizeof(Inode), 1, disk);
            break;
        };

        inode_number++;
    };
    
    fclose(disk);
    printf("Se ha creado un archivo con nombre: %32s\n", filename);
    return 0;
};

#endif