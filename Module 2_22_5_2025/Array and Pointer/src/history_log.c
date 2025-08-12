#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history_log.h"

HistoryNode_t* history_head = NULL;

void history_log_activity(const char* entry) {
    HistoryNode_t* newNode = (HistoryNode_t*)malloc(sizeof(HistoryNode_t));
    if (!newNode) {
        printf("Loi cap phat bo nho!\n");
        return;
    }
    strncpy(newNode->log_entry, entry, sizeof(newNode->log_entry) - 1);
    newNode->log_entry[sizeof(newNode->log_entry) - 1] = '\0';

    newNode->prev = NULL;
    newNode->next = history_head;

    if (history_head != NULL) {
        history_head->prev = newNode;
    }
    history_head = newNode;
}

void history_navigate(void) {
    if (!history_head) {
        printf("Khong co nhat ky nao.\n");
        return;
    }

    HistoryNode_t* current = history_head;
    char cmd;

    printf("Dang o muc moi nhat: %s\n", current->log_entry);
    printf("Nhap lenh (n: next, p: previous, q: quit):\n");

    while (1) {
        printf("> ");
        cmd = getchar();
        while (getchar() != '\n');

        if (cmd == 'n') {
            if (current->next) {
                current = current->next;
                printf(">> %s\n", current->log_entry);
            } else {
                printf(">> Da o cuoi danh sach.\n");
            }
        } else if (cmd == 'p') {
            if (current->prev) {
                current = current->prev;
                printf(">> %s\n", current->log_entry);
            } else {
                printf(">> Da o dau danh sach.\n");
            }
        } else if (cmd == 'q') {
            break;
        } else {
            printf("Lenh khong hop le!\n");
        }
    }
}

void free_history_log(void) {
    HistoryNode_t* curr;
    while (history_head) {
        curr = history_head;
        history_head = history_head->next;
        free(curr);
    }
}
