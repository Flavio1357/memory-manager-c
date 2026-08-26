#include <stdlib.h>
#include "memory.h"

Block *memory_init(void) {
    
    Block *memory = block_create(0, MEMORY_SIZE, 1);

    return memory;
}

void memory_destroy(Block *memory){
    while (memory != NULL){
        Block *next = memory->next;

        free(memory);

        memory = next;
    }
}