#ifndef GET_SUPERBLOCK_H
#define GET_SUPERBLOCK_H

#include <stdio.h>
#include "fs.h"

Superblock get_superblock () {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("get_superblock: Ha ocurrido un error.");
        return (Superblock) {0};
    };

    Superblock sb;

    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    fclose(disk);
    return sb;
};

#endif