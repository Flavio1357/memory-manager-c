#include <stdlib.h>
#include "allocator.h"

Block *allocate_first_fit(Block *memory, size_t size) {

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

int free_memory(Block *memory, size_t start) {
    Block *current = memory;

    while (current != NULL) {
        if (current->start == start && !current->free) {

            current->free = 1;

            return 1;
        }

        current = current->next;
    }

    return 0;
}