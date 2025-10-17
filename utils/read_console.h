#ifndef READ_CONSOLE_H
#define READ_CONSOLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../fs.h"
#include "clear_buffer.h"

Buffer read_console() {
    clear_buffer();

    unsigned long reserved = 128;
    unsigned long size = 0;

    char* buffer = malloc(reserved);
    if (!buffer) return (Buffer){NULL, 0};

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        buffer[size++] = c;

        if (size >= reserved - 1) {
            reserved *= 2;
            char* tmp = realloc(buffer, reserved);
            if (!tmp) {
                free(buffer);
                return (Buffer){NULL, 0};
            }
            buffer = tmp;
        }
    }

    buffer[size] = '\0';
    return (Buffer){ buffer, size };
}

#endif