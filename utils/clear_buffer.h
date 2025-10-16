#ifndef CLEAR_BUFFER_H
#define CLEAR_BUFFER_H

#include <stdio.h>

int clear_buffer () {
    int c;
    while ((c = getchar()) != '\n' && c!= EOF);
};

#endif