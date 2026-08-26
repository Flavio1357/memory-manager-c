#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>
#include "block.h"

typedef enum {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
} AllocationStrategy;

Block *allocate_first_fit(Block *memory, size_t size);

Block *allocate_best_fit(Block *memory, size_t size);

Block *allocate(Block *memory, size_t size, AllocationStrategy AllocationStrategy);

int free_memory(Block *memory, size_t start);

void coalesce_blocks(Block *memory);

#endif