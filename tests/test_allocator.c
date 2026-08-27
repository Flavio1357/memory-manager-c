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


void test_invalid_allocation(void) {

    Block *memory = memory_init();

    if (memory == NULL) {
        printf("[FAIL] Invalid Allocation: memoria nao inicializada.\n");
        return;
    }

    Block *block = allocate(memory, 0, FIRST_FIT);

    if (block == NULL) {
        printf("[PASS] Invalid Allocation - zero bytes\n");
    } else {
        printf("[FAIL] Invalid Allocation - zero bytes\n");
    }

    memory_destroy(memory);
}

void test_allocation_too_large(void) {

    Block *memory = memory_init();

    if (memory == NULL) {
        printf("[FAIL] Too Large: memoria nao inicializada.\n");
        return;
    }

    Block *block = allocate(memory, 1025, FIRST_FIT);

    if (block == NULL) {
        printf("[PASS] Allocation Too Large\n");
    } else {
        printf("[FAIL] Allocation Too Large\n");
    }

    memory_destroy(memory);
}


void test_invalid_free(void) {

    Block *memory = memory_init();

    if (memory == NULL) {
        printf("[FAIL] Invalid Free: memoria nao inicializada.\n");
        return;
    }

    if (free_memory(memory, 9999) == 0) {
        printf("[PASS] Invalid Free\n");
    } else {
        printf("[FAIL] Invalid Free\n");
    }

    memory_destroy(memory);
}

void test_double_free(void) {

    Block *memory = memory_init();

    if (memory == NULL) {
        printf("[FAIL] Double Free: memoria nao inicializada.\n");
        return;
    }

    Block *block = allocate(memory, 200, FIRST_FIT);

    if (block == NULL) {
        printf("[FAIL] Double Free: alocacao inicial falhou.\n");
        memory_destroy(memory);
        return;
    }

    int first_free = free_memory(memory, 0);
    int second_free = free_memory(memory, 0);

    if (first_free == 1 && second_free == 0) {
        printf("[PASS] Double Free Protection\n");
    } else {
        printf("[FAIL] Double Free Protection\n");
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

    test_invalid_allocation();
    test_allocation_too_large();
    test_invalid_free();
    test_double_free();

    return 0;
}