#ifndef BLOCK_H
#define BLOCK_H

#include <stddef.h>

typedef struct Block {
    size_t start;
    size_t size;
    int free;
    struct Block *next;
} Block;


Block *block_create(size_t start, size_t size, int free);

void block_print(const Block *block);

#endif