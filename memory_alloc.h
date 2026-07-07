#ifndef MEMORY_ALLOC_H
#define MEMORY_ALLOC_H

#include <stddef.h>

void* memory_alloc(size_t size);
void cust_free(void* ptr);

#endif