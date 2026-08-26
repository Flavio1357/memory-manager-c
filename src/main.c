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

    printf("\nAlocando 200 bytes...\n\n");

    Block *allocated = allocate_first_fit(memory, 200);

    if (allocated == NULL) {
        printf("Erro: nao foi possivel alocar memoria.\n");
    } else {
        printf("Memoria alocada com sucesso!\n");
    }

    printf("\nMemoria apos alocacao:\n");
    block_print_all(memory);

    memory_destroy(memory);

    return 0;
}