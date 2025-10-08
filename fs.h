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
// 512 Bytes
// 44 Bytes de datos utiles (por ahora)
typedef struct __attribute__((packed)) {
    char fs_name[4]; // 4 Bytes
    char fs_gap1[2]; // 2 Bytes
    char fs_subject[4]; // 4 Bytes
    char fs_gap2[2]; // 2 Bytes

    unsigned int total_blocks; // 4 Bytes
    unsigned int block_size; // 4 Bytes

    unsigned int total_inodes; // 4 Bytes
    unsigned int inode_size; // 4 Bytes

    unsigned int starting_inode_block; // 4 Bytes
    unsigned int starting_data_block; // 4 Bytes
} Superblock; // packed para que el compilador no ponga bytes de relleno en memoria

// Inode representa un archivo
// 256 Bytes
// 41 Bytes datos utiles
typedef struct __attribute__((packed)) {
    char is_used[1]; // 1 Byte
    unsigned int starting_block; // 4 Bytes
    char filename[32]; // 32 Bytes
    char filetype[4]; // 4 Bytes
} Inode;

// Block es la unidad minima de organizacion
typedef struct __attribute__((packed)) {
    char is_used[1]; // 1 B
    unsigned int previous_block; // 4B
    unsigned int next_block; // 4B
    char data[503]; // 503B
} Block;

#endif