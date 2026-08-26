#ifndef MEMORY_H
#define MEMORY_H

#include "block.h"

#define MEMORY_SIZE 1024

Block *memory_init(void);
void memory_destroy(Block *memory);

#endif