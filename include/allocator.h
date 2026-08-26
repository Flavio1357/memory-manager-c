#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "block.h"

Block *allocate_first_fit(Block *memory, size_t size);

#endif