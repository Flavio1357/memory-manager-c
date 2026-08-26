#include <stdlib.h>
#include "memory.h"

Block *memory_init(void) {
    Block *memory = malloc(sizeof(Block));

    if(memory == NULL){
        return NULL;
    }

    memory->start = 0;
    memory->size = MEMORY_SIZE;
    memory->free = 1;
    memory->next = NULL;

    return memory;
}

void memory_destroy(Block *memory){
    while (memory != NULL){
        Block *next = memory->next;

        free(memory);

        memory = next;
    }
}