#ifndef CONTACT_H
#define CONTACT_H

/* Structure to store a single contact's details */
typedef struct Contact_data
{
    char Name[32];          // Contact's name (max 31 chars + null terminator)
    char Mobile_number[11]; // Mobile number (10 digits + null terminator)
    char Mail_ID[35];       // Email ID (max 34 chars + null terminator)
} Contacts;

/* Structure to store the entire address book */
typedef struct AddressBook_Data
{
    Contacts contact_details[100]; // Array of contacts (max 100)
    int contact_count;             // Current number of contacts stored
} AddressBook;

/* Function declarations */

// Initialize address book (set count to 0, etc.)
void init_intitalization(AddressBook *);

// Create a new contact (adds details to the address book)
int create_contact(AddressBook *);

// Display all saved contacts in sorted order
void list_contacts(AddressBook *);

// Search contacts by name, number, or email
int search_contacts(AddressBook *);

// Edit details of an existing contact
int edit_contact(AddressBook *);

// Delete a contact from the address book
int delete_contact(AddressBook *);

// Save contacts to a file 
int save_contacts(AddressBook *);

// Load contacts from a file 
void load_contacts(AddressBook *);

#endif // CONTACT_H
