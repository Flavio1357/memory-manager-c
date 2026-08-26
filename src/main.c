#include <stdio.h>
#include "memory.h"

int main(void) {

    Block *memory = memory_init();

    if (memory == NULL) {
        printf("Erro ao inicializar a memoria.\n");
        return 1;
    }

    printf("=================================\n");
    printf("        MEMORY MANAGER\n");
    printf("=================================\n");

    printf("Inicio: %zu\n", memory->start);
    printf("Tamanho: %zu bytes\n", memory->size);
    printf("Estado: %s\n", memory->free ? "LIVRE" : "OCUPADO");

    memory_destroy(memory);

    return 0;
}