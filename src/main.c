#include <stdio.h>
#include "memory.h"
#include "block.h"

int main(void) {

    Block *memory = memory_init();

    if (memory == NULL) {
        printf("Erro ao inicializar a memoria.\n");
        return 1;
    }

    printf("=================================\n");
    printf("        MEMORY MANAGER\n");
    printf("=================================\n\n");

    printf("Blocos de memoria:\n");

    block_print_all(memory);

    memory_destroy(memory);

    return 0;
}