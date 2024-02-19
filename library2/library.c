#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define STRING_SIZE (254 + 1)
#define MAX_EMAIL_LENGTH (254 + 1)
#define MAX_NAME_LENGTH (254 + 1)
#define MAX_PW_LENGTH (254 + 1)

typedef struct
{
    char buffer[STRING_SIZE];
    unsigned int size;
} Input;

typedef struct
{
    char *email;
    char *name;
    char *pw;
    bool isAdmin;
} Account;

typedef struct
{
    Account *account;
    size_t memory_size;
    int num_accounts;
    int num_admins;
    void *heap_ptr;
} AccountList;

void GetInput(Input *input)
{
    if(scanf_s("%s", input->buffer, input->size) == 0)
    {
        printf("Error: Input too long.\n\n");
        exit(EXIT_FAILURE);
    }
}

void BoundaryCheck(AccountList *account_list)
{
    if((char*)account_list->heap_ptr > (char *) account_list->account + account_list->memory_size)
    {
        printf("Error: Not enough heap memory.\n\n");
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    AccountList account_list = {.account = NULL, .memory_size = 0, .num_accounts = 1, .num_admins = 0, .heap_ptr = NULL};
    account_list.memory_size =
        (account_list.num_accounts * sizeof(Account)) +
        (account_list.num_accounts * (MAX_EMAIL_LENGTH) * sizeof(char)) +
        (account_list.num_accounts * (MAX_NAME_LENGTH) * sizeof(char)) +
        (account_list.num_accounts * (MAX_PW_LENGTH) * sizeof(char));
    account_list.account = malloc(account_list.memory_size);
    (char *) account_list.heap_ptr = (char *) account_list.account + (sizeof(char *) + sizeof(char *) + sizeof(char *));
    Input input = {.buffer = NULL, .size = STRING_SIZE};

    for(size_t i = 0; i < account_list.num_accounts; i++)
    {
        printf_s("email: ");
        GetInput(&input);
        account_list.account[i].email = account_list.heap_ptr;
        (char *) account_list.heap_ptr += (strlen(input.buffer) + 1) * sizeof(char);
        BoundaryCheck(&account_list);
        if(strcpy_s(account_list.account[i].email, (strlen(input.buffer) + 1), input.buffer))
        {
            printf("Error: Data too long.\n\n");
            exit(EXIT_FAILURE);
        }
        printf_s("name: ");
        GetInput(&input);
        account_list.account[i].name = account_list.heap_ptr;
        (char *) account_list.heap_ptr += (strlen(input.buffer) + 1) * sizeof(char);
        BoundaryCheck(&account_list);
        if(strcpy_s(account_list.account[i].name, (strlen(input.buffer) + 1), input.buffer))
        {
            printf("Error: Data too long.\n\n");
            exit(EXIT_FAILURE);
        }
    }
    for(size_t i = 0; i < account_list.num_accounts; i++)
    {
        printf("email[%d]: %s\n", i, account_list.account[i].email);
        printf("name[%d]: %s\n", i, account_list.account[i].name);
    }
    free(account_list.account);
    return 0;
}