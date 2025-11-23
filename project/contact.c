/*Address Book project-its working is similar to a telephone directory.It has functionalities like create a new contact, search the contacts, edit contacts, delete contacts and save.
It validates inputs (like names, mobile numbers, and emails) to ensure correctness.  
The program provides a menu-driven interface for managing contact information efficiently.  */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"//including the header files

// Validation

int isalpha_check(const char*str)//is a function to check if name contains only alphabets
{
    for(int i=0; str[i]!='\0'; i++) {//runs loop throught string
        if(!isalpha(str[i]) && str[i]!=' ') {//uses the inbuilt function to check it shld consist only of alphabet and space
            return 0;//immeadiately returns if fails
        }
    }
    return 1;//else passesthe condition
}

int isnum_check(const char*no) //checks if input is valid number
{
    if(strlen(no)!=10){//checks if number is only of length 10 {
        printf("\033[1;31mEnter only a 10 digit number!\033[0m\n");//else prints error msg if not of length 10
        return 0;
    }
    for(int i=0; no[i]!='\0'; i++) {
        if(!isdigit(no[i])) {//checks if all characters are digit
            printf("\033[1;31mEnter only digits starting from 6-9!\033[0m\n");
            return 0;
        }
    }
    if(no[0]<'6' || no[0]>'9') {//checks if starting numbers is 6-9 for valid number
        printf("\033[1;31mEnter only digits starting from 6-9!\033[0m\n");
        return 0;
    }
    return 1;
}

int is_email(const char* email){ //function that checks valid input{
    int length = strlen(email);//checks the length of e-mail

    if (length < 7) {//minimum length of email shld be eg:t@g.com
        printf("\033[1;31mInvalid Email: Must be at least 7 characters long!\033[0m\n");
        return 0;
    }
    if (strcmp(email + length - 4, ".com") != 0){ //checks if last indexes are .com{
        printf("\033[1;31mInvalid Email: Must end with '.com'.\033[0m\n");
        return 0;
    }
    if (!islower(email[0]))//first letter shld be 0 
    {
        printf("\033[1;31mInvalid Email: First character must be lowercase.\033[0m\n");
        return 0;
    }

    int count = 0, index = -1;
    for (int i = 0; i < length; i++) {
        if (email[i] == '@') {//checking if @ is present
            count++;
            index = i;
        }
        else if (!(isalnum(email[i]) || email[i] == '.' || email[i] == '_')) {//entire email shld only consist of @,.,_-special charcaters
            printf("\033[1;31mInvalid Email: Contains invalid special characters.\033[0m\n");
            return 0;
        }
    }
    if (count != 1) {//checks the @ shld be only once in the entire mail
        printf("\033[1;31mInvalid Email: Must contain exactly one '@'.\033[0m\n");
        return 0;
    }
    if (index <= 0 || index >= length - 5) {//checks if the index of @ shldnt be less than or eqal to @ (@g.com-wrong) also cant be after the domain name (g@.com-wrong)
        printf("\033[1;31mInvalid Email: '@' must be before the domain name.\033[0m\n");
        return 0;
    }
    return 1;
}

int isuniquee(const AddressBook*a,const char *num)//checks if the number is unique 
{
    for(int i=0;i<a->contact_count;i++) {
        // inside isuniquee
        if(strcmp(a->contact_details[i].Mobile_number,num)==0) {
        //printf("\033[1;31mEnter unique number\033[0m\n");
        return 0;
    }   

        }
    
    return 1;
}

int isunique_email(const AddressBook *a, const char *email) {//checks if the email is unique by running it inside the loop
    for (int i = 0; i < a->contact_count; i++) {
        if (strcmp(a->contact_details[i].Mail_ID, email) == 0) {
            return 0;
        }
    }
    return 1;
}

//Contact Creation 

int create_contact(AddressBook *addressbook) {
    char c;
    while (1) {//
        Contacts *newcontact = &addressbook->contact_details[addressbook->contact_count];//creating a varible array of structures with datatype contact details to stores all new values from user

        // Name validation
        while (1) {
            printf("Enter the name\n");
            scanf(" %[^\n]", newcontact->Name);//takes input and stores it in the particular field of array
            if (isalpha_check(newcontact->Name)) break;//checks if everything is alphabets through function
            else printf("\033[1;31mEnter valid name only with alphabets\033[0m\n");
        }
// Mobile number validation
while (1) {
    printf("Enter the number\n");
    scanf("%s", newcontact->Mobile_number);

    // Check if number contains only digits
    if (!isnum_check(newcontact->Mobile_number)) continue;

    // Ensure phone number is unique in addressbook
    if (!isuniquee(addressbook, newcontact->Mobile_number)) {
        printf("\033[1;31mEnter a unique phone number\033[0m\n");
        continue;
    }
    break; // valid number → exit loop
}

// Email validation
while (1) {
    printf("Enter the email id\n");
    scanf("%s", newcontact->Mail_ID);

    // Check email format validity
    if (!is_email(newcontact->Mail_ID)) continue;

    // Ensure email is unique in addressbook
    if (!isunique_email(addressbook, newcontact->Mail_ID)) {
        printf("\033[1;31mEnter unique and valid email-id\033[0m\n");
        continue;
    }
    break; // valid email → exit loop
}

// Contact added
addressbook->contact_count++; // increment total contacts
printf("Contact Added Successfully!\n");

// Ask user if they want to add more contacts
while (1) {
    printf("Do you want to add more contacts? (Y/N): ");
    scanf(" %c", &c);
    if (c == 'y' || c == 'Y') {
        break; // continue outer loop
    } else if (c == 'n' || c == 'N') {
        return 1; // exit function
    } else {
        printf("\033[1;31mInvalid choice. Please enter Y or N only.\033[0m\n");
    }
}
}
}

// List Contacts
void list_contacts(AddressBook *addressbook) {
    if (addressbook->contact_count == 0) {
        printf("\033[1;31mNo contacts to display!\033[0m\n\n"); 
        return;
    }

    // Create array of pointers for sorting without modifying original
    Contacts *sorted[100];
    for (int i = 0; i < addressbook->contact_count; i++) {
        sorted[i] = &addressbook->contact_details[i];
    }

    // Simple bubble-sort by name
    for (int i = 0; i < addressbook->contact_count - 1; i++) {
        for (int j = i + 1; j < addressbook->contact_count; j++) {
            if (strcmp(sorted[i]->Name, sorted[j]->Name) > 0) {
                Contacts *temp = sorted[i]; // swap pointers
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }

    // Display in formatted table
    printf("\033[1;35mTotal contacts: %d\033[0m\n\n", addressbook->contact_count);
    printf("\033[1;33m+-----+----------------------+-----------------+---------------------------+\033[0m\n");
    printf("\033[1;33m| No. | Name                 | Phone           | Email                     |\033[0m\n");
    printf("\033[1;33m+-----+----------------------+-----------------+---------------------------+\033[0m\n");

    for (int i = 0; i < addressbook->contact_count; i++) {
        Contacts *c = sorted[i];
        printf("| %-3d | \033[1;32m%-20s\033[0m | \033[1;36m%-15s\033[0m | \033[1;34m%-25s\033[0m |\n",
               i + 1, c->Name, c->Mobile_number, c->Mail_ID);
    }
    printf("\033[1;33m+-----+----------------------+-----------------+---------------------------+\033[0m\n\n");
}

// Search Contacts
static int indexArr[100];  // stores matching indices
static int dupCount = 0;   // number of matches found
static int searchMode = 0; // 0 = menu loop, 1 = return result (edit/delete)

int search_contacts(AddressBook *addressbook) {
    dupCount = 0;
    int option;
    char input[100];

    while (1) {
        printf("\nSearch Contact Menu:\n");
        printf("1. Name\n2. Mobile number\n3. Mail ID\n4. Exit\n");
        printf("Enter the option: ");
        
        // Validate numeric input
        if (scanf("%d", &option) != 1) {
            printf("\033[1;31mInvalid input. Please enter a number.\033[0m\n");
            while (getchar() != '\n'); // clear input buffer
            continue;
        }

        dupCount = 0;

        // Match based on user option
        switch(option) {
            case 1:
                printf("Enter Name to search: ");
                scanf(" %[^\n]", input);
                for (int i = 0; i < addressbook->contact_count; i++) {
                    if (strcmp(addressbook->contact_details[i].Name, input) == 0)
                        indexArr[dupCount++] = i; // store index of match
                }
                break;

            case 2:
                printf("Enter Mobile number to search: ");
                scanf("%s", input);
                for (int i = 0; i < addressbook->contact_count; i++) {
                    if (strcmp(addressbook->contact_details[i].Mobile_number, input) == 0)
                        indexArr[dupCount++] = i;
                }
                break;

            case 3:
                printf("Enter Mail ID to search: ");
                scanf("%s", input);
                for (int i = 0; i < addressbook->contact_count; i++) {
                    if (strcmp(addressbook->contact_details[i].Mail_ID, input) == 0)
                        indexArr[dupCount++] = i;
                }
                break;

            case 4:
                return -1; // exit search

            default:
                printf("\033[1;31mInvalid option. Try again.\033[0m\n");
                continue;
        }

        // Display results
        if (dupCount == 0) {
            printf("No matching contact found.\n");
        } else if (dupCount == 1) {
            int i = indexArr[0];
            printf("\nContact found: %s | %s | %s\n",
                   addressbook->contact_details[i].Name,
                   addressbook->contact_details[i].Mobile_number,
                   addressbook->contact_details[i].Mail_ID);
            if (searchMode) return i; // return for edit/delete
        } else {
            // Multiple matches → show list
            printf("\nMultiple matches found:\n");
            for (int j = 0; j < dupCount; j++) {
                int i = indexArr[j];
                printf("%d. %s | %s | %s\n", j+1,
                       addressbook->contact_details[i].Name,
                       addressbook->contact_details[i].Mobile_number,
                       addressbook->contact_details[i].Mail_ID);
            }
            if (searchMode) return -2; // signal duplicates
        }

        if (searchMode == 0) continue;
    }
}

// Edit Contacts
int edit_contact(AddressBook *addressbook) {
    printf("Editing Contacts\n");
    searchMode = 1; // enable return mode for search
    while (1) {
        int result = search_contacts(addressbook);
        if (result == -1) { searchMode = 0; return 0; }

        int targetIndex = -1;

        // If only one match
        if (result >= 0) {
            targetIndex = result;
        }
        // If multiple matches, refine by mobile/email
        else if (result == -2) {
            int refineOpt;
            char input[100];
            while (targetIndex == -1) {
                printf("\nRefine duplicates by:\n1. Mobile\n2. Email\n3. Cancel\nChoice: ");
                scanf("%d", &refineOpt);
                if (refineOpt == 1) {
                    printf("Enter Mobile: ");
                    scanf("%s", input);
                    for (int j = 0; j < dupCount; j++) {
                        int idx = indexArr[j];
                        if (strcmp(addressbook->contact_details[idx].Mobile_number, input) == 0)
                            targetIndex = idx;
                    }
                } else if (refineOpt == 2) {
                    printf("Enter Email: ");
                    scanf("%s", input);
                    for (int j = 0; j < dupCount; j++) {
                        int idx = indexArr[j];
                        if (strcmp(addressbook->contact_details[idx].Mail_ID, input) == 0)
                            targetIndex = idx;
                    }
                } else {
                    printf("\033[1;31mCancelled.\033[0m\n");
                    break;
                }
            }
        }

        if (targetIndex == -1) continue;

        Contacts *c = &addressbook->contact_details[targetIndex];
        int choice;
        char temp[100];

        printf("\nEditing: %s | %s | %s\n", c->Name, c->Mobile_number, c->Mail_ID);
        printf("1. Name\n2. Mobile\n3. Email\n4. All\n5. Back to Search Menu\nChoice: ");
        scanf("%d",&choice);

        switch(choice) {
            case 1:
                // Update name with alphabet-only validation
                while (1) {
                    printf("Enter new name: ");
                    scanf(" %[^\n]", temp);
                    if (isalpha_check(temp)) { // validate alphabets only
                        strcpy(c->Name, temp); // copy to struct
                        break;
                    } else printf("Invalid name! Use alphabets only.\n");
                }
                break;
            case 2:
                // Update mobile with digit-only + uniqueness validation
                while (1) {
                    printf("Enter new mobile: ");
                    scanf("%s", temp);
                    if (isnum_check(temp) && isuniquee(addressbook, temp)) {
                        strcpy(c->Mobile_number, temp); // update
                        break;
                    } else {
                        printf("Invalid/duplicate number! Try again.\n");
                    }
                }
                break;
            case 3:
                // Update email with format + uniqueness validation
                while (1) {
                    printf("Enter new email: ");
                    scanf("%s", temp);
                    if (is_email(temp) && isunique_email(addressbook, temp)) {
                        strcpy(c->Mail_ID, temp); // update
                        break;
                    } else {
                        printf("Invalid/duplicate email! Try again.\n");
                    }
                }
                break;
            case 4:
                // Update all fields (name, mobile, email)
                while (1) {
                    printf("Enter new name: ");
                    scanf(" %[^\n]", temp);
                    if (isalpha_check(temp)) //checks if input is alphabets only 
                        { 
                            strcpy(c->Name, temp); //then copies the input into the field
                            break; 
                        }
                    else 
                    printf("Invalid name! Use alphabets only.\n");
                }
                while (1) {
                    printf("Enter new mobile: ");
                    scanf("%s", temp);
                    if (isnum_check(temp) && isuniquee(addressbook, temp))//checks if number is unique and is valid number using function
                    {
                        strcpy(c->Mobile_number, temp);
                        break;
                    } else {
                        printf("Invalid/duplicate number! Try again.\n");
                    }
                }
                while (1) {
                    printf("Enter new email: ");
                    scanf("%s", temp);
                    if (is_email(temp) && isunique_email(addressbook, temp)) {
                        strcpy(c->Mail_ID, temp);
                        break;
                    } else {
                        printf("Invalid/duplicate email! Try again.\n");
                    }
                }
                break;
            case 5:
                continue;
            default:
                printf("Invalid choice!\n");
        }

        printf("Contact updated successfully!\n");
    }
    searchMode = 0;
    return 1;
}

// Delete Contacts
int delete_contact(AddressBook *addressbook) {
    searchMode = 1;
    while (1) {
        int result = search_contacts(addressbook);
        if (result == -1) { searchMode = 0; return 0; }

        int targetIndex = -1;

        // Direct match
        if (result >= 0) {
            targetIndex = result;
        }
        // Handle duplicates
        else if (result == -2) {
            int refineOpt;
            char input[100];
            while (targetIndex == -1) {
                printf("\nRefine duplicates by:\n1. Mobile\n2. Email\n3. Cancel\nChoice: ");
                scanf("%d", &refineOpt);
                if (refineOpt == 1) {
                    printf("Enter Mobile: ");
                    scanf("%s", input);
                    for (int j = 0; j < dupCount; j++) {
                        int idx = indexArr[j];
                        if (strcmp(addressbook->contact_details[idx].Mobile_number, input) == 0)
                            targetIndex = idx;
                    }
                } else if (refineOpt == 2) {
                    printf("Enter Email: ");
                    scanf("%s", input);
                    for (int j = 0; j < dupCount; j++) {
                        int idx = indexArr[j];
                        if (strcmp(addressbook->contact_details[idx].Mail_ID, input) == 0)
                            targetIndex = idx;
                    }
                } else {
                    printf("Cancelled.\n");
                    break;
                }
            }
        }

        if (targetIndex == -1) continue;

        printf("Deleting: %s , %s , %s\n",
            addressbook->contact_details[targetIndex].Name,
            addressbook->contact_details[targetIndex].Mobile_number,
            addressbook->contact_details[targetIndex].Mail_ID);

        // Shift contacts left to overwrite deleted one
        for (int i = targetIndex; i < addressbook->contact_count - 1; i++) {
            addressbook->contact_details[i] = addressbook->contact_details[i + 1];
        }
        addressbook->contact_count--; // reduce total count

        printf("Contact deleted successfully!\n");
    }
    searchMode = 0;
    return 1;
}
