#define FUSE_USE_VERSION 31
#include <fuse3/fuse.h>
#include "./fuse_ops/fuse_operations.h"

int main (int argc, char *argv[]) {
    return fuse_main(argc, argv, &bbfs_ops, NULL);
};