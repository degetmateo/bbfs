#ifndef BBFS_GETATTR_H
#define BBFS_GETATTR_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fuse3/fuse.h>

#include "../fs.h"
#include "../open_disk.h"
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fuse3/fuse.h>

int bbfs_getattr (const char * path, struct stat * st, struct fuse_file_info * fi) {
    memset(st, 0, sizeof(struct stat));

    if (strcmp(path, "/") == 0) {
        st->st_mode = __S_IFDIR | 0755;
        st->st_nlink = 2;
        return 0;
    };

    const char *filename = path + 1;

    FILE *disk = open_disk();

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Inode inode;
    fseek(disk, sb.first_inode_block_offset * sb.block_size, SEEK_SET);

    unsigned int inode_number = 1;
    while (fread(&inode, sizeof(Inode), 1, disk) == 1) {
        if (inode_number > sb.total_inodes) {
            perror("bbfs_open: No se ha encontrado el archivo.");
            fclose(disk);
            return -ENOENT;
        };

        if (strcmp(inode.filename, filename) == 0) {
            st->st_mode = __S_IFREG | 0644;
            st->st_nlink = 1;
            st->st_size = sizeof(Inode);
            st->st_atime = st->st_mtime = st->st_ctime = time(NULL);
            
            fclose(disk);
            return 0;      
        };
    };

    fclose(disk);
    return -ENOENT;
};

#endif