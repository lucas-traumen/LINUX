
#ifndef MEMORY_LAB_H
#define MEMORY_LAB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Node {
    void *p;
    struct Node *next;
} Node;

void recurse_overflow(size_t depth);
void leak_until_oom(size_t chunk_size);

#endif
