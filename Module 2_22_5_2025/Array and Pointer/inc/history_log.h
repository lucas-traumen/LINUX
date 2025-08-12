#ifndef HISTORY_LOG_H
#define HISTORY_LOG_H

typedef struct HistoryNode {
    char log_entry[50];
    struct HistoryNode* next;
    struct HistoryNode* prev;
} HistoryNode_t;

extern HistoryNode_t* history_head;

void history_log_activity(const char* entry);
void history_navigate(void);
void free_history_log(void);

#endif
