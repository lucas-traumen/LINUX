#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_ACCOUNT_NUMBER     20
#define SIFE_OF_ACCOUNT_HOLDER     500

// Define the BankAccount structure
typedef struct {
    char accountNumber[SIZE_OF_ACCOUNT_NUMBER];
    char accountHolder[SIFE_OF_ACCOUNT_HOLDER];
    double balance;
} BankAccount;

static BankAccount* bankAccountInstance = NULL;

int checkDuplicateAccount(const char* accountNumber, const char* accountHolder) {
    if (bankAccountInstance == NULL) return 0;

    // So sánh nếu trùng
    if (strcmp(bankAccountInstance->accountNumber, accountNumber) == 0 &&
        strcmp(bankAccountInstance->accountHolder, accountHolder) == 0) {
        printf("⚠️  Dữ liệu trùng lặp. Hủy tài khoản hiện tại.\n");
        destroyBankAccount();
        return 1; // Đã trùng và đã hủy
    }
    return 0; // Không trùng
}
// Function to create or get the unique BankAccount instance
BankAccount* createBankAccount(const char* accountNumber, const char* accountHolder, double balance) {
    if (bankAccountInstance != NULL) {
        printf("Error: A bank account already exists! Cannot create another one.\n");
        return NULL;
    }

    // Create a bank account if it does not already exist
    bankAccountInstance = (BankAccount*)malloc(sizeof(BankAccount));
    if (bankAccountInstance != NULL) {
         if (!checkDuplicateAccount(accountNumber, accountHolder)) {
        snprintf(bankAccountInstance->accountNumber, sizeof(bankAccountInstance->accountNumber), "%s", accountNumber);
        snprintf(bankAccountInstance->accountHolder, sizeof(bankAccountInstance->accountHolder), "%s", accountHolder);
        bankAccountInstance->balance = balance;
         }
    }
    return bankAccountInstance;
}

// Function to destroy the BankAccount instance
void destroyBankAccount() {
    if (bankAccountInstance != NULL) {
        free(bankAccountInstance);
        bankAccountInstance = NULL;
    }
}

int main() {
    // Create the first bank account
    BankAccount* account1 = createBankAccount("0853955884", "Lucas_Tri", 0.0);
    if (account1 != NULL) {
        printf("Account 1 created:\n");
        printf("Account Number: %s\n", account1->accountNumber);
        printf("Account Holder: %s\n", account1->accountHolder);
        printf("Balance: %.2f\n\n", account1->balance);
    }

    // Attempt to create a second bank account
    BankAccount* account2 = createBankAccount("0853955884", "Lucas_Tri", 0.0);
    if (account2 == NULL) {
        printf("Failed to create Account 2 because an account already exists.\n\n");
    }

    // Display the current account
    printf("Current Bank Account:\n");
    printf("Account Number: %s\n", bankAccountInstance->accountNumber);
    printf("Account Holder: %s\n", bankAccountInstance->accountHolder);
    printf("Balance: %.2f\n\n", bankAccountInstance->balance);

    // Destroy the bank account
    destroyBankAccount();
    printf("Bank account destroyed.\n");

    return 0;
}
