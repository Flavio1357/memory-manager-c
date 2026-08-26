#include <stdio.h>
#include <stdlib.h>
#include "block.h"

Block *block_create(size_t start, size_t size, int free){
    Block *block = malloc(sizeof(Block));

    if(block == NULL){
        return NULL;
    }

    block->start = start;
    block->size = size;
    block->free = free;
    block->next = NULL;

    return block;
}

void block_print(const Block *block){

    if(block == NULL){
        return;
    }

    printf("Inicio: %zu | Tamanho: %zu | Estado: %s\n", block->start, block->size, block->free ? "LIVRE" : "OCUPADO");
}