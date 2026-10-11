#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

int validatePhone(char *phone)
{
    int count = 0;

    for (int i = 0; phone[i] != '\0'; i++)
    {
        if (phone[i] >= '0' && phone[i] <= '9')
        {
            count++;
        }
        else
        {
            return 0;
        }
    }

    if (count != 10)
    {
        return 0;
    }

    if (phone[0] != '6' && phone[0] != '7' && phone[0] != '8' && phone[0] != '9')
    {
        return 0;
    }

    return 1;
}

int validateEmail(char *email)
{
    int len = strlen(email);

    if (len < 11)
    {
        return 0;
    }

    if (!(email[0] >= 'a' && email[0] <= 'z'))
    {
        return 0;
    }

    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == ' ')
        {
            return 0;
        }

        if (email[i] >= 'A' && email[i] <= 'Z')
        {
            return 0;
        }
    }

    int atCount = 0;

    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            atCount++;
        }
    }

    if (atCount != 1)
    {
        return 0;
    }

    // Check @ position
    char *at = strchr(email, '@');

    if (at == email)
    {
        return 0;
    }

    if (*(at + 1) == '\0')
    {
        return 0;
    }

    // Must end with @gmail.com
    if (strcmp(email + len - 10, "@gmail.com") != 0)
    {
        return 0;
    }

    return 1;
}

int validateEmpty(char *str)
{
    if (strlen(str) == 0)
    {
        return 0;
    }

    return 1;
}

void listContacts(AddressBook *addressBook)
{
    // Sort contacts based on the chosen criteria

    if (addressBook->contactCount == 0)
    {
        printf("\nNo Contacts Available!\n");
        return;
    }

    sortContacts(addressBook);

    printf("\n");
    printf("============================================================\n");
    printf("                     CONTACT LIST\n");
    printf("============================================================\n");

    printf("%-5s %-20s %-15s %-25s\n", "ID", "NAME", "PHONE", "EMAIL");

    printf("------------------------------------------------------------");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("\n%-5d %-20s %-15s %-25s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    printf("============================================================\n");
}

void sortContacts(AddressBook *addressBook)
{
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - 1 - i; j++)
        {
            if (strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
}

void initialize(AddressBook *addressBook)
{
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int validateName(char *name) 
{
    if (strlen(name) == 0) 
    {
        return 0;
    }
    for (int i = 0; name[i] != '\0'; i++) 
    {
        char c = name[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) && c != ' ') 
        {
            return 0;
        }
    }
    return 1;
}

void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */

    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("\nAddress Book is Full!\n");
        return;
    }

    int i = addressBook->contactCount;

    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                      CREATE CONTACT                      ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");

    do
    {
        printf("Enter name : ");
        scanf(" %49[^\n]", addressBook->contacts[i].name);

        if (!validateName(addressBook->contacts[i].name))
        {
            printf("Invalid name! Use alphabets and spaces only.\n");
        }

    } while (!validateName(addressBook->contacts[i].name));

    do
    {
        printf("Enter phone number : ");
        scanf(" %[^\n]", addressBook->contacts[i].phone);

        if (!validatePhone(addressBook->contacts[i].phone))
        {
            printf("Invalid phone number! Enter exactly 10 digits and number should start from 6,7,8,9.\n");
        }

    } while (!validatePhone(addressBook->contacts[i].phone));

    do
    {
        printf("Enter your mail id : ");
        scanf(" %[^\n]", addressBook->contacts[i].email);

        if (!validateEmail(addressBook->contacts[i].email))
        {
            printf("Invalid Gmail! Enter a valid @gmail.com address.\n");
        }

    } while (!validateEmail(addressBook->contacts[i].email));

    if (!validateEmpty(addressBook->contacts[i].name))
    {
        printf("\nName cannot be empty!\n");
        return;
    }

    if (!validatePhone(addressBook->contacts[i].phone))
    {
        printf("\nInvalid phone number!\n");
        return;
    }

    if (!validateEmail(addressBook->contacts[i].email))
    {
        printf("\nInvalid email address!\n");
        return;
    }

    for (int j = 0; j < i; j++)
    {
        if (strcmp(addressBook->contacts[j].phone, addressBook->contacts[i].phone) == 0)
        {
            printf("\nPhone number already exists!\n");
            printf("Contact was not added.\n");
            return;
        }
    }

    for (int j = 0; j < i; j++)
    {
        if (strcmp(addressBook->contacts[j].email, addressBook->contacts[i].email) == 0)
        {
            printf("\nEmail already exists!\n");
            printf("Contact was not added.\n");
            return;
        }
    }

    addressBook->contactCount++;

    sortContacts(addressBook);

    printf("\n");
    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│               Contact added successfully!                │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");
}

void searchContact(AddressBook *addressBook)
{
    /* Define the logic for search */

    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts to search.\n");
        return;
    }

    int option;
    char searchTerm[50];
    int found = 0;

    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                      SEARCH CONTACT                      ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");

    printf("Search by : \n1. Name\n2. Phone\n3. Email\n");

    printf("Enter Your choice : ");
    scanf("%d", &option);

    printf("Enter search value : ");
    scanf(" %49[^\n]", searchTerm);

    switch (option)
    {
    case 1:

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].name, searchTerm) == 0)
            {
                printf("\nContact Found!\n");
                printf("------------------------------------------------------------");
                printf("\nName : %s, Phone : %s, Email : %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("------------------------------------------------------------");
                found = 1;
                break;
            }
        }
        break;

    case 2:

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, searchTerm) == 0)
            {
                printf("\nContact Found!\n");
                printf("------------------------------------------------------------");
                printf("\nName : %s, Phone : %s, Email : %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("------------------------------------------------------------");
                found = 1;
                break;
            }
        }
        break;

    case 3:

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, searchTerm) == 0)
            {
                printf("\nContact Found!\n");
                printf("------------------------------------------------------------");
                printf("\nName : %s, Phone : %s, Email : %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("------------------------------------------------------------");
                found = 1;
                break;
            }
        }
        break;

    default:
        printf("Invalid Option!\n");
        return;
    }

    if (found == 0)
        printf("\nContact not found.\n");
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */

    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts to edit!\n");
        return;
    }

    int option;
    char searchTerm[50];
    int index = -1;
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                       EDIT CONTACT                       ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");

    printf("Search contact by : \n1. Name\n2. Phone\n3. Email\n");
    printf("Enter your choice : ");
    scanf("%d", &option);

    printf("Enter search value : ");
    scanf(" %[^\n]", searchTerm);

    switch (option)
    {
    case 1:

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].name, searchTerm) == 0)
            {
                index = i;
                break;
            }
        }
        break;

    case 2:

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, searchTerm) == 0)
            {
                index = i;
                break;
            }
        }
        break;

    case 3:

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, searchTerm) == 0)
            {
                index = i;
                break;
            }
        }
        break;

    default:
        printf("Invalid Option!\n");
        return;
    }

    if (index == -1)
    {
        printf("\nContact not found.\n");
        return;
    }

    printf("\nCurrent Contact Details\n");
    printf("------------------------------------------------------------");
    printf("\nName : %s\n", addressBook->contacts[index].name);
    printf("Phone : %s\n", addressBook->contacts[index].phone);
    printf("Email : %s\n", addressBook->contacts[index].email);
    printf("------------------------------------------------------------");

    switch (option)
    {
    case 1:
        do
        {
            printf("Enter new name : ");
            scanf(" %[^\n]", addressBook->contacts[index].name);

            if (!validateName(addressBook->contacts[index].name))
            {
                printf("Invalid name! Use alphabets and spaces only.\n");
            }

        } while (!validateName(addressBook->contacts[index].name));

        break;

    case 2:
        do
        {
            printf("Enter new phone : ");
            scanf(" %[^\n]", addressBook->contacts[index].phone);

            if (!validatePhone(addressBook->contacts[index].phone))
            {
                printf("Invalid phone number! Enter exactly 10 digits.\n");
            }

        } while (!validatePhone(addressBook->contacts[index].phone));

        break;

    case 3:
        do
        {
            printf("Enter new email : ");
            scanf(" %[^\n]", addressBook->contacts[index].email);

            if (!validateEmail(addressBook->contacts[index].email))
            {
                printf("Invalid Gmail! Enter a valid @gmail.com address.\n");
            }

        } while (!validateEmail(addressBook->contacts[index].email));

        break;
    }
    sortContacts(addressBook);

    printf("\nContact Updated Successfully!\n");
}

void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deletecontact */

    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts to delete!\n");
        return;
    }

    int option;
    char searchTerm[50];
    int index = -1;

    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                      DELETE CONTACT                      ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");

    printf("\nDelete contact by : \n1. Name\n2. Phone\n3. Email\n");
    printf("Enter your choice : ");
    scanf("%d", &option);

    printf("Enter search value : ");
    scanf(" %[^\n]", searchTerm);

    switch (option)
    {
    case 1:

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].name, searchTerm) == 0)
            {
                index = i;
                break;
            }
        }
        break;

    case 2:

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, searchTerm) == 0)
            {
                index = i;
                break;
            }
        }
        break;

    case 3:

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, searchTerm) == 0)
            {
                index = i;
                break;
            }
        }
        break;

    default:
        printf("\nInvalid Option!\n");
        return;
    }

    if (index == -1)
    {
        printf("\nContact not found!\n");
        return;
    }

    printf("\nContact found : \n");
    printf("------------------------------------------------------------");
    printf("\nName : %s\n", addressBook->contacts[index].name);
    printf("Phone : %s\n", addressBook->contacts[index].phone);
    printf("Email : %s\n", addressBook->contacts[index].email);
    printf("------------------------------------------------------------");

    char confirm[5];
    printf("\nAre you sure you want to delete this contact (Yes/No) : ");
    scanf(" %4s", confirm);

    if (strcmp(confirm, "yes") == 0 || strcmp(confirm, "Yes") == 0 || strcmp(confirm, "YES") == 0)
    {
        for (int i = index; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }

        addressBook->contactCount--;

        printf("\nContact Deleted Successfully!\n");
    }
    else
    {
        printf("\nDeletion Cancelled.\n");
    }
}
