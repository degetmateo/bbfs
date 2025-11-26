#ifndef BBFS_READDIR_H
#define BBFS_READDIR_h

#include <fuse3/fuse.h>
#include "../fs.h"
#include "../open_disk.h"
#include "../get_superblock.h"
#include <errno.h>

int bbfs_readdir (const char* path, void* buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info* fi, enum fuse_readdir_flags flags) {
    FILE *disk = open_disk();
    if (!disk) return -EIO; 

    filler(buf, ".", NULL, 0, (enum fuse_fill_dir_flags) 0);
    filler(buf, "..", NULL, 0, (enum fuse_fill_dir_flags) 0);

    if (strcmp(path, "/") != 0) return -ENOENT;

    Superblock sb;
    fseek(disk, 0, SEEK_SET);
    fread(&sb, sizeof(Superblock), 1, disk);

    Inode inode;
    fseek(disk, sb.first_inode_block_offset * sb.block_size, SEEK_SET);
    
    int inode_number = 1;
    while (fread(&inode, sizeof(Inode), 1, disk) == 1) {
        if (inode_number > sb.total_inodes) {
            break;
        };

        if (!inode.is_used) {
            inode_number++;
            continue;
        };

        struct stat st;
        memset(&st, 0, sizeof(st));
        st.st_mode = __S_IFREG | 0644;
        st.st_nlink = 1;
        st.st_size = sizeof(inode);

        filler(buf, inode.filename, &st, 0, (enum fuse_fill_dir_flags) 0);
        inode_number++;
    };

    fclose(disk);
    return 0;
};

#endif