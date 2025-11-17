#ifndef FS_H
#define FS_H
#include <stdio.h>

// char 1 byte
// short 2 bytes
// int 4 bytes
// long 8 bytes
// size_t = unsigned long 

// Superblock es el primer bloque del sistema de archivos
// Contiene metadatos especiales sobre el sistema de archivos
typedef struct __attribute__((packed)) {
    char name[4];                           // 4 Bytes, 4B
    char detail[4];                         // 4 Bytes, 8B

    unsigned int total_blocks;              // 4 Bytes, 12B
    unsigned int block_size;                // 4 Bytes, 16B

    unsigned int total_inodes;              // 4 Bytes, 20B
    unsigned int inode_size;                // 4 Bytes, 24B

    unsigned int first_data_block_offset;   // 4 Bytes, 28B
    unsigned int first_inode_block_offset;  // 4 Bytes, 32B

    unsigned int block_data_size;           // 4B, 36B

    char reserved[92];                      // 92 Bytes, 128B
} Superblock; // packed para que el compilador no ponga bytes de relleno en memoria

// Inode representa un archivo
typedef struct __attribute__((packed)) {
    char is_used;                           // 1 Byte
    unsigned int starting_block_offset;     // 4 Bytes
    char filename[32];                      // 32 Bytes
    char reserved[91];                      // 91 Bytes
} Inode;                                    // 128 Bytes en total

typedef struct __attribute__((packed)) {
    char is_used;                           // 1 Byte
    unsigned int next_block_offset;         // 4 Bytes
    char data[59];                          // 59 Bytes

    unsigned char prev_hash[32];            // 32 Bytes - primer bloque con genesis, para los demas es el hash del anterior
    unsigned char hash[32];                 // 32 Bytes - data + prev_hash
} Block;                                    // 128 Bytes en total

typedef struct {
    char *data;
    unsigned long size;
} Buffer;

#endif