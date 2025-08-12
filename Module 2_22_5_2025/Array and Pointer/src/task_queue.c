#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task_queue.h"

TaskNode_t* task_head = NULL;
TaskNode_t* task_tail = NULL;

void queue_add_task(const char* description) {
    TaskNode_t* newNode = (TaskNode_t*)malloc(sizeof(TaskNode_t));
    if (!newNode) {
        printf("Loi cap phat bo nho!\n");
        return;
    }
    strncpy(newNode->task_description, description, sizeof(newNode->task_description) - 1);
    newNode->task_description[sizeof(newNode->task_description) - 1] = '\0';
    newNode->next = NULL;

    if (task_tail == NULL) {
        task_head = task_tail = newNode;
    } else {
        task_tail->next = newNode;
        task_tail = newNode;
    }
}

TaskNode_t* queue_get_next_task(void) {
    if (task_head == NULL) return NULL;

    TaskNode_t* temp = task_head;
    task_head = task_head->next;
    if (task_head == NULL) {
        task_tail = NULL;
    }
    return temp;
}

void print_task_queue(void) {
    TaskNode_t* curr = task_head;
    printf("Hang doi tac vu:\n");
    while (curr) {
        printf(" - %s\n", curr->task_description);
        curr = curr->next;
    }
    if (!task_head) {
        printf(" <Rong>\n");
    }
}

void free_task_queue(void) {
    TaskNode_t* curr;
    while (task_head) {
        curr = task_head;
        task_head = task_head->next;
        free(curr);
    }
    task_tail = NULL;
}
