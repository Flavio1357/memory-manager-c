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

    if (allocate(memory, 200, FIRST_FIT) != NULL) {
        printf("200 bytes alocados com sucesso!\n");
    }

    block_print_all(memory);

    printf("\n---------------------------------\n");
    printf("Alocando 300 bytes...\n");
    printf("---------------------------------\n");

    if (allocate(memory, 300, FIRST_FIT) != NULL) {
        printf("300 bytes alocados com sucesso!\n");
    }

    block_print_all(memory);

    printf("\n---------------------------------\n");
    printf("Alocando 100 bytes...\n");
    printf("---------------------------------\n");

    if (allocate(memory, 100, FIRST_FIT) != NULL) {
        printf("100 bytes alocados com sucesso!\n");
    }

    block_print_all(memory);

    printf("\n---------------------------------\n");
    printf("Liberando bloco iniciado em 200...\n");
    printf("---------------------------------\n");

    if (free_memory(memory, 200)) {
        printf("Memoria liberada com sucesso!\n");
    } else {
        printf("Erro: bloco nao encontrado.\n");
    }

    block_print_all(memory);

    printf("\n---------------------------------\n");
    printf("Liberando bloco iniciado em 500...\n");
    printf("---------------------------------\n");

    if (free_memory(memory, 500)) {
        printf("Memoria liberada com sucesso!\n");
    } else {
        printf("Erro: bloco nao encontrado.\n");
    }

    block_print_all(memory);

    printf("\n---------------------------------\n");
    printf("Testando alocacao invalida...\n");
    printf("---------------------------------\n");

    if (allocate(memory, 0, FIRST_FIT) == NULL) {
        printf("Teste 1: alocacao de 0 bytes rejeitada.\n");
    } else {
        printf("Teste 1: ERRO.\n");
    }

    if (allocate(memory, 2000, FIRST_FIT) == NULL) { 
        printf("Teste 2: alocacao maior que a memoria rejeitada.\n");
    } else {
        printf("Teste 2: ERRO.\n");
    }

    memory_destroy(memory);

    return 0;
}