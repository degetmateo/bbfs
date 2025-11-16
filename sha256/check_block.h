#ifndef CHECK_BLOCK_H
#define CHECK_BLOCK_H

#include <string.h>

#include "../fs.h"
#include "hash.h"

int check_block (unsigned char data[59], unsigned char prev_hash[32], unsigned char actual_hash[32]) {
    unsigned char rehashed[32];

    hash(data, prev_hash, rehashed);

    printf("%32s\n", rehashed);
    printf("%32s\n", actual_hash);

    return memcmp(rehashed, actual_hash, 32);
};

#endif