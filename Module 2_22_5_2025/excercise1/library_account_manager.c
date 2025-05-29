#include "library_account_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Singleton instance
static LibraryAccountManager* ManagerInstance = NULL;

// take and create account 
LibraryAccountManager* LibraryManager_GetInstance(void) {
    if (ManagerInstance == NULL) {
        ManagerInstance = (LibraryAccountManager*)malloc(sizeof(*ManagerInstance));
        if (ManagerInstance) {
            ManagerInstance->initialized = 0;
        }
    }
    return ManagerInstance;
}

int LibraryManager_CreateAccount(const char* readerId,
                                 const char* readerName) {
    LibraryAccountManager* AccountManager = LibraryManager_GetInstance();
    if (!AccountManager) {
        return ERR_NO_MEMORY;
    }

    if (AccountManager->initialized) {
        // 1) Duplicate?
        if (strcmp(AccountManager->account.readerId, readerId) == 0 &&
            strcmp(AccountManager->account.readerName, readerName) == 0) {
            printf(" Duplicate reader account detected. Resetting manager.\n");
            LibraryManager_Destroy();
            return ERR_DUPLICATE;
        }
        // 2) Already exists another
        printf(" A reader account already exists. Cannot create another.\n");
        return ERR_ALREADY_EXISTS;
    }

    // No existing account: initialize new one
    strncpy(AccountManager->account.readerId, readerId, MAX_ID_LEN - 1);
    AccountManager->account.readerId[MAX_ID_LEN - 1] = '\0';

    strncpy(AccountManager->account.readerName, readerName, MAX_NAME_LEN - 1);
    AccountManager->account.readerName[MAX_NAME_LEN - 1] = '\0';

    AccountManager->account.booksBorrowed = 0;
    AccountManager->initialized = 1;

    printf(" Reader account created: %s - %s\n",
           AccountManager->account.readerId, AccountManager->account.readerName);
    return ERR_SUCCESS;
}

void LibraryManager_Display(const LibraryAccountManager* AccountManager ) {
    if (!AccountManager || !AccountManager->initialized) {
        printf(" No reader account to display.\n");
        return;
    }
    printf("\n Library Account Info:\n");
    printf(" - Reader ID      : %s\n", AccountManager->account.readerId);
    printf(" - Reader Name    : %s\n", AccountManager->account.readerName);
    printf(" - Books Borrowed : %d\n\n", AccountManager->account.booksBorrowed);
}

void LibraryManager_Destroy(void) {
    if (ManagerInstance) {
        free(ManagerInstance);
        ManagerInstance = NULL;
        printf("✅ LibraryAccountManager destroyed.\n");
    }
}

