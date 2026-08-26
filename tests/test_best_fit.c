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

    /*
     * Criando um cenario para testar o Best Fit.
     *
     * Memoria inicial:
     *
     * [1024 LIVRE]
     *
     * Alocamos:
     * 100 + 500 + 200
     *
     * Resultado:
     *
     * [100 USADO][500 USADO][200 USADO][224 LIVRE]
     */

    allocate(memory, 100, FIRST_FIT);
    allocate(memory, 500, FIRST_FIT);
    allocate(memory, 200, FIRST_FIT);

    /*
     * Liberamos os blocos de 100 e 200.
     *
     * Resultado:
     *
     * [100 LIVRE][500 USADO][200 LIVRE][224 LIVRE]
     */

    free_memory(memory, 0);
    free_memory(memory, 600);

    printf("=================================\n");
    printf("          TESTE BEST FIT\n");
    printf("=================================\n\n");

    printf("Memoria antes da alocacao:\n");
    block_print_all(memory);

    printf("\nAlocando 150 bytes com BEST FIT...\n\n");

    Block *allocated = allocate(memory, 150, BEST_FIT);

    if (allocated != NULL) {
        printf("150 bytes alocados com sucesso!\n");
        printf("Bloco escolhido: inicio = %zu\n", allocated->start);
    } else {
        printf("Falha na alocacao.\n");
    }

    printf("\nMemoria depois da alocacao:\n");
    block_print_all(memory);

    memory_destroy(memory);

    return 0;
}