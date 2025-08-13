#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "memory_lab.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <stack_overflow|memory_leak|out_of_memory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "stack_overflow") == 0) {
        printf("Triggering stack overflow (recursive calls)...\n");
        fflush(stdout);
        /* Bắt đầu đệ quy */
        recurse_overflow(1);
    } else if (strcmp(argv[1], "memory_leak") == 0 ||
               strcmp(argv[1], "out_of_memory") == 0) {
        /* Kích thước 1 KB = 1024 bytes (theo yêu cầu) */
        size_t chunk = 1024;
        leak_until_oom(chunk);
    } else {
        fprintf(stderr, "Unknown mode: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}