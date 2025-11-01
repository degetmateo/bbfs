#ifndef OPEN_DISK_H
#define OPEN_DISK_H

#include <stdio.h>

FILE* open_disk () {
    FILE *disk = fopen("disk.bbfs", "r+b");

    if (!disk) {
        perror("open_disk: Ha ocurrido un error.");
        return NULL;
    };

    return disk;
};

#endif