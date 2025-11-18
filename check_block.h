#ifndef CHECK_BLOCK_H
#define CHECK_BLOCK_H

#include <string.h>

#include "utils/print_bytes.h"
#include "fs.h"
#include "./sha256/hash.h"

int check_block (unsigned char data[59], unsigned char prev_hash[32], unsigned char actual_hash[32]) {
    unsigned char rehashed[32];

    // printf("check_block\n\n");
    printf("HASH RECREATION\n");
    printf("HASH RECREATION DATA\n");
    print_bytes(data, 59);
    printf("HASH RECREATION PREV_HASH\n");
    print_bytes(prev_hash, 32);

    printf("check_block_actual_hash\n");
    print_bytes(actual_hash, 32);

    hash(data, prev_hash, rehashed);

    printf("rehashed_result\n");
    print_bytes(rehashed, 32);

    return memcmp(rehashed, actual_hash, 32);
};

#endif