#include "library_account_manager.h"

int main(void) {
   
    LibraryManager_CreateAccount("R001", "Lucas Tri ");
    LibraryManager_Display(LibraryManager_GetInstance());


    LibraryManager_CreateAccount("R001", "Lucas Tri");
    LibraryManager_Display(LibraryManager_GetInstance());


    LibraryManager_CreateAccount("R002", "Bob");
    LibraryManager_Display(LibraryManager_GetInstance());

  
    LibraryManager_Destroy();
    return 0;
}

