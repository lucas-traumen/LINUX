#ifndef LIBRARY_ACCOUNT_MANAGER_H
#define LIBRARY_ACCOUNT_MANAGER_H

#include <stddef.h>

#define MAX_NAME_LEN   100
#define MAX_ID_LEN      20
#define ERR_SUCCESS            0   
#define ERR_DUPLICATE         -1   
#define ERR_ALREADY_EXISTS    -2  
#define ERR_NO_MEMORY         -3   

// libary account's information
typedef struct {
    char readerId[MAX_ID_LEN];
    char readerName[MAX_NAME_LEN];
    int  booksBorrowed;
} LibraryAccount;

// Singleton manager
typedef struct {
    LibraryAccount account;
    int            initialized;
} LibraryAccountManager;

// Take only a acoount
LibraryAccountManager* LibraryManager_GetInstance(void);

int LibraryManager_CreateAccount(const char* readerId,
                                 const char* readerName);


void LibraryManager_Display(const LibraryAccountManager* mgr);


void LibraryManager_Destroy(void);

#endif  // LIBRARY_ACCOUNT_MANAGER_H

