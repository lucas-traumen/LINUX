#include "memory_lab.h"


static volatile int sink = 0; 

void recurse_overflow(size_t depth) {
    char buffer[1024];
    buffer[0] = (char)(depth & 0xFF);
    sink += buffer[0];
    if (depth % 100 == 0) {
        printf("[recursion] depth = %zu\n", depth);
        fflush(stdout);
    }
    recurse_overflow(depth + 1);
    (void) sink;
}

void leak_until_oom(size_t chunk_size) {
    Node *head = NULL;
    size_t count = 0;

    printf("Start leaking, allocating %zu bytes per loop...\n", chunk_size);
    fflush(stdout);

    while (1) {
        void *mem = malloc(chunk_size);
        if (!mem) {
            fprintf(stderr, "malloc returned NULL after %zu allocations of %zu bytes (approx %zu KB)\n",
                    count, chunk_size, (count * chunk_size) / 1024);
            exit(EXIT_FAILURE);
        }
        /* Use memory a bit to ensure allocation */
        ((char*)mem)[0] = 0xA5;

        Node *n = (Node*)malloc(sizeof(Node));
        if (!n) {
            fprintf(stderr, "Failed to allocate tracking node; exiting\n");
            exit(EXIT_FAILURE);
        }
        n->p = mem;
        n->next = head;
        head = n;

        count++;
        if ((count % 1000) == 0) {
            printf("[leak] allocated %zu blocks (approx %zu KB)\n", count, (count * chunk_size) / 1024);
            fflush(stdout);
        }
    }
}