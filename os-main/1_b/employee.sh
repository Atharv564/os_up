#!/bin/bash

# Constants for the maximum records
MAX_RECORDS=100
NAME_LENGTH=50
PHONE_LENGTH=15
EMAIL_LENGTH=50

# Address book entries array
declare -A addressBook
recordCount=0

# Function to display the menu
display_menu() {
    echo -e "\nAddress Book Menu:"
    echo "1) Create address book"
    echo "2) View address book"
    echo "3) Insert a record"
    echo "4) Delete a record"
    echo "5) Modify a record"
    echo "6) Exit"
}

# Function to create a new address book (reset entries)
create_address_book() {
    addressBook=() # Reset the address book to empty
    recordCount=0
    echo "Address book created successfully."
}

# Function to view the entire address book
view_address_book() {
    if [[ $recordCount -eq 0 ]]; then
        echo "Address book is empty."
    else
        echo "Address Book Contents:"
        for i in "${!addressBook[@]}"; do
            echo -e "\nRecord $((i+1))"
            echo "Name: ${addressBook[$i,name]}"
            echo "Phone: ${addressBook[$i,phone]}"
            echo "Email: ${addressBook[$i,email]}"
        done
    fi
}

# Function to insert a new record
insert_record() {
    if [[ $recordCount -ge $MAX_RECORDS ]]; then
        echo "Address book is full. Cannot insert new record."
        return
    fi

    echo -n "Enter name: "
    read -r name
    echo -n "Enter phone number: "
    read -r phone
    echo -n "Enter email address: "
    read -r email

    addressBook[$recordCount,name]=$name
    addressBook[$recordCount,phone]=$phone
    addressBook[$recordCount,email]=$email

    ((recordCount++))
    echo "Record inserted successfully."
}

# Function to delete a record based on the name
delete_record() {
    echo -n "Enter the name of the record to delete: "
    read -r name

    local found=-1
    for i in "${!addressBook[@]}"; do
        if [[ "${addressBook[$i,name]}" == "$name" ]]; then
            found=$i
            break
        fi
    done

    if [[ $found -eq -1 ]]; then
        echo "Record not found."
    else
        for ((j=found; j<recordCount-1; j++)); do
            addressBook[$j,name]=${addressBook[$((j+1)),name]}
            addressBook[$j,phone]=${addressBook[$((j+1)),phone]}
            addressBook[$j,email]=${addressBook[$((j+1)),email]}
        done
        unset addressBook[$((recordCount-1)),name]
        unset addressBook[$((recordCount-1)),phone]
        unset addressBook[$((recordCount-1)),email]
        ((recordCount--))
        echo "Record deleted successfully."
    fi
}

# Function to modify a record based on the name
modify_record() {
    echo -n "Enter the name of the record to modify: "
    read -r name

    local found=-1
    for i in "${!addressBook[@]}"; do
        if [[ "${addressBook[$i,name]}" == "$name" ]]; then
            found=$i
            break
        fi
    done

    if [[ $found -eq -1 ]]; then
        echo "Record not found."
    else
        echo -n "Modify phone number (current: ${addressBook[$found,phone]}): "
        read -r phone
        echo -n "Modify email (current: ${addressBook[$found,email]}): "
        read -r email

        addressBook[$found,phone]=$phone
        addressBook[$found,email]=$email
        echo "Record modified successfully."
    fi
}

# Main script
while true; do
    display_menu
    echo -n "Enter your choice: "
    read -r choice

    case $choice in
        1)
            create_address_book
            ;;
        2)
            view_address_book
            ;;
        3)
            insert_record
            ;;
        4)
            delete_record
            ;;
        5)
            modify_record
            ;;
        6)
            echo "Exiting the program. Goodbye!"
            exit 0
            ;;
        *)
            echo "Invalid choice. Please try again."
            ;;
    esac
done
