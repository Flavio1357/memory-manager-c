#include <stdlib.h>
#include "allocator.h"

Block *allocate_first_fit(Block *memory, size_t size) {

    if(memory == NULL || size == 0){
        return NULL;
    }

    Block *current = memory;

    while (current != NULL) {
        if (current->free && current->size >= size) {

            if (current->size > size) {

                Block *new_block = block_create(
                    current->start + size,
                    current->size - size,
                    1
                );

                if (new_block == NULL) {
                    return NULL;
                }

                new_block->next = current->next;
                current->next = new_block;
            }

            current->size = size;
            current->free = 0;

            return current;
        }

        current = current->next;
    }

    return NULL;
}


Block *allocate_best_fit(Block *memory, size_t size) {

    if (memory == NULL || size == 0) {
        return NULL;
    }

    Block *current = memory;
    Block *best = NULL;

    while (current != NULL) {
        if (current->free && current->size >= size) {

            if (best == NULL || current->size < best->size) {
                best = current;
            }
        }

        current = current->next;
    }

    if (best == NULL) {
        return NULL;
    }

    if (best->size > size) {

        Block *new_block = block_create(
            best->start + size,
            best->size - size,
            1
        );

        if (new_block == NULL) {
            return NULL;
        }

        new_block->next = best->next;
        best->next = new_block;
    }

    best->size = size;
    best->free = 0;

    return best;
}


Block *allocate_worst_fit(Block *memory, size_t size) {

    if (memory == NULL || size == 0) {
        return NULL;
    }

    Block *current = memory;
    Block *worst = NULL;

    while (current != NULL) {
        if (current->free && current->size >= size) {

            if (worst == NULL || current->size > worst->size) {
                worst = current;
            }
        }

        current = current->next;
    }

    if (worst == NULL) {
        return NULL;
    }

    if (worst->size > size) {

        Block *new_block = block_create(
            worst->start + size,
            worst->size - size,
            1
        );

        if (new_block == NULL) {
            return NULL;
        }

        new_block->next = worst->next;
        worst->next = new_block;
    }

    worst->size = size;
    worst->free = 0;

    return worst;
}


Block *allocate(Block *memory, size_t size, AllocationStrategy strategy) {

    switch (strategy) {

        case FIRST_FIT:
            return allocate_first_fit(memory, size);

        case BEST_FIT:
            return allocate_best_fit(memory, size);

        case WORST_FIT:
            return allocate_worst_fit(memory, size);

        default:
            return NULL;
    }
}


int free_memory(Block *memory, size_t start) {
    Block *current = memory;

    while (current != NULL) {
        if (current->start == start && !current->free) {

            current->free = 1;

            coalesce_blocks(memory);

            return 1;
        }

        current = current->next;
    }

    return 0;
}


void coalesce_blocks(Block *memory) {
    Block *current = memory;

    while (current != NULL && current->next != NULL){
        if(current->free && current->next->free){

            Block *next = current->next;

            current->size += next->size;
            current->next = next->next;

            free(next);

        }else{

            current = current->next;
        }
    }
}