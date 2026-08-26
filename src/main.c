#include <stdio.h>

#include "memory.h"
#include "block.h"
#include "allocator.h"

int main(void) {

    Block *memory = memory_init();

    if (memory == NULL) {
        printf("Erro ao inicializar a memoria.\n");
        return 1;
    }

    printf("=================================\n");
    printf("        MEMORY MANAGER\n");
    printf("=================================\n\n");

    printf("Memoria inicial:\n");
    block_print_all(memory);

    printf("\n---------------------------------\n");
    printf("Alocando 200 bytes...\n");
    printf("---------------------------------\n");

    if (allocate_first_fit(memory, 200) != NULL) {
        printf("200 bytes alocados com sucesso!\n");
    }

    block_print_all(memory);

    printf("\n---------------------------------\n");
    printf("Alocando 300 bytes...\n");
    printf("---------------------------------\n");

    if (allocate_first_fit(memory, 300) != NULL) {
        printf("300 bytes alocados com sucesso!\n");
    }

    block_print_all(memory);

    printf("\n---------------------------------\n");
    printf("Alocando 100 bytes...\n");
    printf("---------------------------------\n");

    if (allocate_first_fit(memory, 100) != NULL) {
        printf("100 bytes alocados com sucesso!\n");
    }

    block_print_all(memory);

    memory_destroy(memory);

    return 0;
}