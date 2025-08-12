#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./inc/task_queue.h"
#include "./inc/history_log.h"

int main(void) {
    char input[100];
    printf("He thong quan ly hang doi va nhat ky\n");

    while (1) {
        printf("\nNhap lenh (add/run/list/history/quit): ");
        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = '\0';

        if (strncmp(input, "add ", 4) == 0) {
            queue_add_task(input + 4);
        }
        else if (strcmp(input, "run") == 0) {
            TaskNode_t* task = queue_get_next_task();
            if (task) {
                printf("Dang thuc hien: %s\n", task->task_description);
                history_log_activity(task->task_description);
                free(task);
            } else {
                printf("Hang doi rong.\n");
            }
        }
        else if (strcmp(input, "list") == 0) {
            print_task_queue();
        }
        else if (strcmp(input, "history") == 0) {
            history_navigate();
        }
        else if (strcmp(input, "quit") == 0) {
            break;
        }
        else {
            printf("Lenh khong hop le.\n");
        }
    }

    free_task_queue();
    free_history_log();
    return 0;
}
