#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

typedef struct {
    const char* name;
    int  (*getStatus)(void);  
} Subsystem;

#endif
