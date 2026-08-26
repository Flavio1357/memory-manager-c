#include <stdio.h>
#include <stdlib.h>

#include "memory.h"
#include "allocator.h"

void test_first_fit(void) {

    Block *memory = memory_init();

    if (memory == NULL) {
        printf("[FAIL] First Fit: memoria nao inicializada.\n");
        return;
    }

    Block *block = allocate(memory, 200, FIRST_FIT);

    if (block != NULL &&
        block->start == 0 &&
        block->size == 200 &&
        block->free == 0) {

        printf("[PASS] First Fit\n");

    } else {

        printf("[FAIL] First Fit\n");
    }

    memory_destroy(memory);
}

void test_best_fit(void) {

    Block *memory = memory_init();

    if (memory == NULL) {
        printf("[FAIL] Best Fit: memoria nao inicializada.\n");
        return;
    }

    allocate(memory, 100, FIRST_FIT);
    allocate(memory, 500, FIRST_FIT);
    allocate(memory, 200, FIRST_FIT);

    free_memory(memory, 0);
    free_memory(memory, 600);

    Block *block = allocate(memory, 150, BEST_FIT);

    if (block != NULL &&
        block->start == 600 &&
        block->size == 150 &&
        block->free == 0) {

        printf("[PASS] Best Fit\n");

    } else {

        printf("[FAIL] Best Fit\n");
    }

    memory_destroy(memory);
}

void test_worst_fit(void) {

    Block *memory = memory_init();

    if (memory == NULL) {
        printf("[FAIL] Worst Fit: memoria nao inicializada.\n");
        return;
    }

    allocate(memory, 100, FIRST_FIT);
    allocate(memory, 500, FIRST_FIT);
    allocate(memory, 200, FIRST_FIT);

    free_memory(memory, 0);
    free_memory(memory, 600);

    Block *block = allocate(memory, 150, WORST_FIT);

    if (block != NULL &&
        block->start == 800 &&
        block->size == 150 &&
        block->free == 0) {

        printf("[PASS] Worst Fit\n");

    } else {
        printf("[FAIL] Worst Fit\n");
    }

    memory_destroy(memory);
}

void test_free_memory(void) {

    Block *memory = memory_init();

    if (memory == NULL) {
        printf("[FAIL] Free Memory: memoria nao inicializada.\n");
        return;
    }

    Block *block = allocate(memory, 200, FIRST_FIT);

    if (block == NULL) {
        printf("[FAIL] Free Memory: alocacao inicial falhou.\n");
        memory_destroy(memory);
        return;
    }

    if (free_memory(memory, 0) &&
        memory->free == 1 &&
        memory->size == 1024) {

        printf("[PASS] Free Memory\n");

    } else {

        printf("[FAIL] Free Memory\n");
    }

    memory_destroy(memory);
}

void test_coalescing(void) {

    Block *memory = memory_init();

    if (memory == NULL) {
        printf("[FAIL] Coalescing: memoria nao inicializada.\n");
        return;
    }

    allocate(memory, 100, FIRST_FIT);
    allocate(memory, 200, FIRST_FIT);
    allocate(memory, 300, FIRST_FIT);

    /*
     * Memoria:
     *
     * [100 USADO][200 USADO][300 USADO][424 LIVRE]
     */

    free_memory(memory, 100);
    free_memory(memory, 300);

    /*
     * Agora:
     *
     * [100 USADO][500 LIVRE][300 USADO][424 LIVRE]
     */

    if (memory->next != NULL &&
        memory->next->start == 100 &&
        memory->next->size == 500 &&
        memory->next->free == 1) {

        printf("[PASS] Coalescing\n");

    } else {

        printf("[FAIL] Coalescing\n");
    }

    memory_destroy(memory);
}

int main(void) {

    printf("=================================\n");
    printf("        ALLOCATOR TESTS\n");
    printf("=================================\n\n");

    test_first_fit();
    test_best_fit();
    test_worst_fit();
    test_free_memory();
    test_coalescing();

    return 0;
}