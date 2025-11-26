#ifndef BBFS_OPERATIONS_H
#define BBFS_OPERATIONS_H
#define FUSE_USE_VERSION 31

#include <fuse3/fuse.h>
#include "../operations/bbfs_read.h"
#include "../operations/bbfs_readdir.h"
#include "../operations/bbfs_write.h"
#include "../operations/bbfs_open.h"
#include "../operations/bbfs_getattr.h"
#include <sys/stat.h>

static struct fuse_operations bbfs_ops = {
    .getattr = bbfs_getattr,
    .open = bbfs_open,
    .read = bbfs_read,
    .write = bbfs_write,
    .readdir = bbfs_readdir,
};

#endif