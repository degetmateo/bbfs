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
    Superblock sb = get_superblock();
    Inode inode = get_inode(filename);
    FILE *disk = open_disk();

    free_chained_blocks(inode.starting_block_offset);
    free_block(inode.starting_block_offset);

    free_inode(get_inode_offset(filename));

    fclose(disk);
    return 0;
};

#endif