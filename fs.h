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
    char name[4]; // 4 Bytes, 4B
    char detail[4]; // 4 Bytes, 8B

    unsigned int total_blocks; // 4 Bytes, 12B
    unsigned int block_size; // 4 Bytes, 16B

    unsigned int total_inodes; // 4 Bytes, 20B
    unsigned int inode_size; // 4 Bytes, 24B

    unsigned int starting_inode_block; // 4 Bytes, 28B
    unsigned int starting_data_block; // 4 Bytes, 32B

    unsigned int block_data_size; // 4B, 36B

    char reserved[28];
} Superblock; // packed para que el compilador no ponga bytes de relleno en memoria

// Inode representa un archivo
typedef struct __attribute__((packed)) {
    char is_used; // 1 Byte
    unsigned int starting_block; // 4 Bytes, 5B
    char filename[32]; // 32 Bytes, 37B
    char reserved[27];
} Inode;

// Block es la unidad minima de organizacion
typedef struct __attribute__((packed)) {
    char is_used; // 1 B
    unsigned int next_block; // 4B, 5B
    char data[59]; // 64B, 69B
} Block;

typedef struct {
    char *data;
    unsigned long size;
} Buffer;

#endif