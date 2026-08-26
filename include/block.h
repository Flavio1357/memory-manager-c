#ifndef BLOCK_H
#define BLOCK_H

#include <stddef.h>

typedef struct Block {
    size_t start;
    size_t size;
    int free;
    struct Block *next;
} Block;

#endif