#ifndef PRINT_BYTES_H
#define PRINT_BYTES_H

#include <stdio.h>

int print_bytes (unsigned char* buffer, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        printf("%02x", buffer[i]);
    };

    printf("\n");
    return 0;
};

#endif