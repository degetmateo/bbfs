#ifndef DELETE_FILE_H
#define DELETE_FILE_H

#include <stdio.h>

#include "fs.h"
#include "get_inode.h"

int delete_file (char filename[32]) {
    Inode inode = get_inode(filename);
};

#endif