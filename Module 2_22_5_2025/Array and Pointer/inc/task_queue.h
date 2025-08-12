#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include <stddef.h>

typedef struct TaskNode {
    char task_description[50];
    struct TaskNode* next;
} TaskNode_t;

extern TaskNode_t* task_head;
extern TaskNode_t* task_tail;

void queue_add_task(const char* description);
TaskNode_t* queue_get_next_task(void);
void print_task_queue(void);
void free_task_queue(void);

#endif
