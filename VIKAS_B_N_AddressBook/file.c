#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fp = fopen("contacts.csv" , "w");

    if(fp==NULL)
    {
        printf("\nError opening file for saving!\n");
        return;
    }

    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fp , "%s,%s,%s\n" , addressBook->contacts[i].name , addressBook->contacts[i].phone , addressBook->contacts[i].email);
    }

    fclose(fp);

    printf("\nContacts Saved Successfully!\n");

}

void loadContactsFromFile(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;

    FILE *fp = fopen("contacts.csv" , "r");
    
    if(fp==NULL)
    {
        printf("\nNo existing contacts found.! Start Fresh.\n");
        return;
    }

    char line[150];
    
    while(fgets(line , sizeof(line), fp)  != NULL && addressBook->contactCount < MAX_CONTACTS)
    {
        int i = addressBook->contactCount;

        sscanf(line , "%49[^,],%19[^,],%49[^,\n]" , addressBook->contacts[i].name , addressBook->contacts[i].phone , addressBook->contacts[i].email);

        addressBook->contactCount++;

    }

    fclose(fp);
    printf("\nContacts Loaded Successfully!\n");
    printf("\n");

}
