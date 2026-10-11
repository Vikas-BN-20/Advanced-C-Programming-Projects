/*
PROJECT 1

NAME : VIKAS B N 
DATE : 01/09/2026 to 05/09/2026
DESCRIPTION : TO CREATE ADDRESS BOOK

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

void printHeader()
{
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                       ADDRESS BOOK                       ║\n");
    printf("║                Contact Management System                 ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
}

void printMenu()
{
    printf("\n");
    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│                        MAIN MENU                         │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│   1. Create Contact                                      │\n");
    printf("│   2. Search Contact                                      │\n");
    printf("│   3. Edit Contact                                        │\n");
    printf("│   4. Delete Contact                                      │\n");
    printf("│   5. List Contacts                                       │\n");
    printf("│   6. Save and Exit                                       │\n");
    printf("│   7. Exit                                                │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");
}

int main()
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do
    {
        printHeader();

        printf("\nTotal Contacts : %d / %d\n", addressBook.contactCount, MAX_CONTACTS);

        printMenu();

        printf("Enter your choice : ");
        if (scanf("%d", &choice) != 1)
        {
            clearInputBuffer();
            printf("\nInvalid input. Please enter a number between 1 and 7.\n");
            choice = 0;
            continue;
        }

        switch (choice)
        {
        case 1:
            createContact(&addressBook);
            break;
        case 2:
            searchContact(&addressBook);
            break;
        case 3:
            editContact(&addressBook);
            break;
        case 4:
            deleteContact(&addressBook);
            break;
        case 5:
            listContacts(&addressBook);
            break;
        case 6:
            printf("\n");
            printf("╔══════════════════════════════════════════════════════════╗\n");
            printf("║                  Saving Address Book...                  ║\n");
            printf("║                   Thank you! Goodbye!                    ║\n");
            printf("╚══════════════════════════════════════════════════════════╝\n");

            saveAndExit(&addressBook);
            break;
        case 7:
        {
            char confirm[5];
            printf("\nAre you sure you want to exit this contact without saving (Yes/No) : ");
            if (scanf(" %4s", confirm) != 1)
            {
                clearInputBuffer();
                printf("\nInput not recognized. Exit cancelled.\n");
                break;
            }

            if (strcmp(confirm, "yes") == 0 || strcmp(confirm, "Yes") == 0 || strcmp(confirm, "YES") == 0)
            {
                printf("\nExiting without saving...\n");
                printf("\n");
                exit(EXIT_SUCCESS);
            }
            else
            {
                printf("\nExit Cancelled.\n");
            }
            break;
        }

        default:
            printf("\n");
            printf("┌──────────────────────────────────────────────────────────┐\n");
            printf("│  Invalid choice! Please select between 1 and 7.          │\n");
            printf("└──────────────────────────────────────────────────────────┘\n");
        }

        if (choice != 6)
        {
            printf("\nPress ENTER to continue...\n");
            getchar();
            getchar();
        }
    } while (choice != 6);

    return 0;
}
