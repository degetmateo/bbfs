#ifndef WRITE_FILE_H
#define WRITE_FILE_H

#include <stdio.h>
#include <string.h>

#include "fs.h"

int write_file (char filename[32], char *data) {
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

    int actual_inode = 1;
    while (fread(&inode, sizeof(Inode), 1, disk) == 1) {
        if (actual_inode > sb.total_inodes) {
            perror("write_file: No se ha encontrado el archivo.");
            return -1;
        };

        if (strcmp(filename, inode.filename) == 0) {
            break;
        };

        actual_inode++;
    };

    fclose(disk);
    return 0;
};

int write_block () {

};

#endif