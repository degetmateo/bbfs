#ifndef HASH_H
#define HASH_H

#include <string.h>
#include <openssl/sha.h>

void hash (unsigned char data[59], unsigned char prev_hash[32], unsigned char new_hash[32]) {    
    unsigned char data_to_hash[59 + 32];

    memcpy(data_to_hash, data, 59);
    memcpy(data_to_hash + 59, prev_hash, 32);

    SHA256(data_to_hash, sizeof(data_to_hash), new_hash);
};

#endif