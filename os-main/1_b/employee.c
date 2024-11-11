#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100
#define NAME_LENGTH 50
#define PHONE_LENGTH 15
#define EMAIL_LENGTH 50

// Structure to hold address book entry
typedef struct {
    char name[NAME_LENGTH];
    char phone[PHONE_LENGTH];
    char email[EMAIL_LENGTH];
} AddressBookEntry;

// Function declarations
void create_address_book(AddressBookEntry book[], int *count);
void view_address_book(AddressBookEntry book[], int count);
void insert_record(AddressBookEntry book[], int *count);
void delete_record(AddressBookEntry book[], int *count);
void modify_record(AddressBookEntry book[], int count);
void display_menu();

int main() {
    AddressBookEntry addressBook[MAX_RECORDS];
    int recordCount = 0;
    int choice;

    while (1) {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // To consume the newline character left by scanf
        
        switch (choice) {
            case 1:
                create_address_book(addressBook, &recordCount);
                break;
            case 2:
                view_address_book(addressBook, recordCount);
                break;
            case 3:
                insert_record(addressBook, &recordCount);
                break;
            case 4:
                delete_record(addressBook, &recordCount);
                break;
            case 5:
                modify_record(addressBook, recordCount);
                break;
            case 6:
                printf("Exiting the program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Function to display the menu
void display_menu() {
    printf("\nAddress Book Menu:\n");
    printf("1) Create address book\n");
    printf("2) View address book\n");
    printf("3) Insert a record\n");
    printf("4) Delete a record\n");
    printf("5) Modify a record\n");
    printf("6) Exit\n");
}

// Function to create a new address book (reset entries)
void create_address_book(AddressBookEntry book[], int *count) {
    *count = 0;  // Reset the address book to empty
    printf("Address book created successfully.\n");
}

// Function to view the entire address book
void view_address_book(AddressBookEntry book[], int count) {
    if (count == 0) {
        printf("Address book is empty.\n");
    } else {
        printf("Address Book Contents:\n");
        for (int i = 0; i < count; i++) {
            printf("\nRecord %d\n", i + 1);
            printf("Name: %s\n", book[i].name);
            printf("Phone: %s\n", book[i].phone);
            printf("Email: %s\n", book[i].email);
        }
    }
}

// Function to insert a new record
void insert_record(AddressBookEntry book[], int *count) {
    if (*count >= MAX_RECORDS) {
        printf("Address book is full. Cannot insert new record.\n");
        return;
    }

    printf("Enter name: ");
    fgets(book[*count].name, NAME_LENGTH, stdin);
    book[*count].name[strcspn(book[*count].name, "\n")] = '\0';  // Remove newline

    printf("Enter phone number: ");
    fgets(book[*count].phone, PHONE_LENGTH, stdin);
    book[*count].phone[strcspn(book[*count].phone, "\n")] = '\0';

    printf("Enter email address: ");
    fgets(book[*count].email, EMAIL_LENGTH, stdin);
    book[*count].email[strcspn(book[*count].email, "\n")] = '\0';

    (*count)++;
    printf("Record inserted successfully.\n");
}

// Function to delete a record based on the name
void delete_record(AddressBookEntry book[], int *count) {
    char name[NAME_LENGTH];
    printf("Enter the name of the record to delete: ");
    fgets(name, NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';  // Remove newline

    int found = -1;
    for (int i = 0; i < *count; i++) {
        if (strcmp(book[i].name, name) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Record not found.\n");
    } else {
        // Shift records to delete the specified entry
        for (int i = found; i < *count - 1; i++) {
            book[i] = book[i + 1];
        }
        (*count)--;
        printf("Record deleted successfully.\n");
    }
}

// Function to modify a record based on the name
void modify_record(AddressBookEntry book[], int count) {
    char name[NAME_LENGTH];
    printf("Enter the name of the record to modify: ");
    fgets(name, NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';  // Remove newline

    int found = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(book[i].name, name) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Record not found.\n");
    } else {
        printf("Modify phone number (current: %s): ", book[found].phone);
        fgets(book[found].phone, PHONE_LENGTH, stdin);
        book[found].phone[strcspn(book[found].phone, "\n")] = '\0';

        printf("Modify email (current: %s): ", book[found].email);
        fgets(book[found].email, EMAIL_LENGTH, stdin);
        book[found].email[strcspn(book[found].email, "\n")] = '\0';

        printf("Record modified successfully.\n");
    }
}
