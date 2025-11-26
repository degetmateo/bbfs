#ifndef DELETE_FILE_H
#define DELETE_FILE_H

#include <stdio.h>

#include "fs.h"
#include "get_inode.h"
#include "get_superblock.h"
#include "open_disk.h"
#include "free_block.h"
#include "free_chained_blocks.h"
#include "free_inode.h"
#include "get_inode_offset.h"

int delete_file (char filename[32]) {
    FILE *disk = open_disk();

    if (!disk) {
        return -1;
    };

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Inode inode;
    fseek(disk, (sb.first_inode_block_offset * sb.block_size), SEEK_SET);

    unsigned int inode_number = 1;
    while (fread(&inode, sizeof(Inode), 1, disk) == 1) {
        if (inode_number > sb.total_inodes) {
            perror("delete_file: No se ha encontrado el archivo.");
            fclose(disk);
            return -1;
        }
        
        inode_number++;
        
        if (inode.is_used != 1) {
            continue;
        };

        if (strcmp(filename, inode.filename) == 0) {
            free_chained_blocks(inode.starting_block_offset);
            free_block(inode.starting_block_offset);

            free_inode(get_inode_offset(filename));
            
            break;
        };
    };

    fclose(disk);
    return 0;
};

#endif