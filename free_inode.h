#ifndef FREE_INODE_H
#define FREE_INODE_H

#include <stdio.h>
#include "fs.h"
#include "open_disk.h"
#include "get_superblock.h"

int free_inode (unsigned int inode_offset) {
    Superblock sb = get_superblock();
    FILE *disk = open_disk();

    Inode inode;
    fseek(disk, (sb.first_inode_block_offset + inode_offset) * sb.block_size, SEEK_SET);
    fread(&inode, sizeof(Inode), 1, disk);

    inode.is_used = 0;
    inode.starting_block_offset = 0;

    fseek(disk, -sizeof(Inode), SEEK_CUR);
    fwrite(&inode, sizeof(Inode), 1, disk);

    fclose(disk);
    return 0;
};

#endif