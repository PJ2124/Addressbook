/*
Name: Prathmesh Jadhav
Class :24030A
Project Name: AddressBook 
Date :17/01/2025 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

int index_i ;
int flag ;
int searchResults[MAX_CONTACTS];
int searchCount =0 ;

// Define the logic for list conatact
void listContacts(AddressBook *addressBook )
{
    printf("---------------**********************-------------\n");
    printf(" sr.no \tName \t\tphone no. \tEmail.Id\n ");
    printf("---------------**********************-------------\n");
    // Loop through all contacts in the address book
    for(int i=0; i<addressBook->contactCount ; i++)
    
    {
       int len= strlen(addressBook->contacts[i].name); // Get the length of the name
       if(len > 7)// Align the output based on the length of the name
       {
          printf("%d\t%s\t%s\t%s\n",i + 1 ,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
       }
       else
       {
           printf("%d\t%s\t\t%s\t%s\n",i + 1 ,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
       }
    }
    // Print footer line
    printf("--------------------------------------------------------------------\n");

}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
  loadContactsFromFile(addressBook);
}

// Define the logic for save contact 
void saveAndExit(AddressBook *addressBook) {
   saveContactsToFile(addressBook); // Save contacts to file

    exit(EXIT_SUCCESS); // Exit the program
}


// Validation logic for the name 
int create_name(char *name )
{
   int i, count =0 ;
   int len = strlen(name);

   // Check if all characters in the name are valid (alphabets and spaces)
   for(i = 0; i< len; i++)
   {
       if( (name[i] >= 'A' && name[i] <= 'Z') ||( name[i] >= 'a' && name[i] <= 'z')||(name[i] == ' ') )
       {
           count++;
       }
   }
   // Return validation result
       if(count == len)
       {
           return 1;
       }
       else
       {
           return 0;
       }
   
}
// Validation logic for phone number
int create_phone(char *phone)
{
    int len = strlen(phone);
    int i,  count = 0;
// Check if phone number contains only digits
    for(i=0; i<len; i++)
    {
        if(phone[i] >= '0' && phone[i] <= '9')
        {
            count++;
        }
       
    }
 // Check if phone number has exactly 10 digits
    if(count == 10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Validation logic for email
int create_email(char *email)
{
		int len = strlen(email);
		int i,count =0;
// Check if email contains '.' and '@' in the correct places
		for(i = 0; i <len; i++)
		{
				if(email[i] == '.' || email[i] == '@' )
				{
						if(email[i] == '.' && email[i+1] =='c'&& email[ i + 2 ] == 'o' && email[i+3]== 'm')
						{
								count++;
						}
						else if(email[i] == '@' && email[i+1]!= '.')
						{
								count++;
				     	}
					
				}
		}
		// Email is valid if both '@' and '.' are present in the right positions
		if (count ==2)
		{
				return 1;
		}
		else
		{
				return 0;
		}

}



// Define the logic for to create a contact
void createContact(AddressBook *addressBook)
{

label1 :
  // user for a name and validate
   printf("Enter the name :");
   scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);
   int valid;
 // Validate the name
   valid = create_name(addressBook->contacts[addressBook->contactCount].name);  // funcation call  return valid 
   if(valid == 0) 
    {
       printf("Invalid name\n");
       goto label1;// Retry if invalid
    }

label2:  
 // user for a phone number and validate
    printf("Enter the number ");
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].phone);
// Validate the phone number
   valid = create_phone(addressBook->contacts[addressBook->contactCount].phone);
   if(valid == 0) 
   {
       printf("Invalid phone.no\n");
       goto label2;// Retry if invalid
   }
    // Check if the phone number already exists in the address book
   else{
     char *phone ;
     int i ; 
// Check if phone number already exists
    for(i=0; i<addressBook->contactCount;i++)
    {
        phone = strstr(addressBook->contacts[i].phone,addressBook->contacts[addressBook->contactCount].phone) ;
        if (phone != NULL) // If phone number already exists
        { 
           printf("Phone number already exit , Please try again.\n");
           goto label2 ;// Retry if duplicate
        }

    }
   }
label3:
 // user for an email address and validate
   printf("Enter the email :");  
   scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].email); 
  // Validate the email   
   valid = create_email(addressBook->contacts[addressBook->contactCount].email);
   if (valid == 0)
   {
      printf("Invalid Input \n");
  
     goto label3 ;// Retry if invalid
   }
// Add the new contact to the address book
      addressBook->contactCount++;
      printf("Contact created successfully.\n");
    
}

// Define the logic for search contact 
void searchContact(AddressBook *addressBook) {
    int option, val;// 'option' stores the user's choice of search criteria
    int found = 0;// 'found' is a flag to indicate if a contact foud  
    searchCount = 0; // Reset the search count to 0 each time the function is called.
// Step 1: Ask the user how they would like to search for a contact.
    printf("Search contact by :\n 1. Name\n 2. Phone\n 3. Email\nEnter choice : ");
    scanf("%d", &option);

    switch(option)
    {
        case 1: // Case 1: Search by Name
 search1:
            {// Step 2: Ask the user to input a name.
            printf("Enter name : ");
            scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);
// Step 3: Validate the name 
            val = create_name(addressBook->contacts[addressBook->contactCount].name);
            if (val == 1) {// If the name is valid:
// Step 4: Loop through all contacts and check if any contact name contains the search string.
                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strstr(addressBook->contacts[i].name, addressBook->contacts[addressBook->contactCount].name)) {
// If a match is found, display the contact and store its index in `searchResults`.
                        printf("%d. %s\t%s\t%s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        searchResults[searchCount++] = i; // Store the index of found contact
                        found = 1;  // Set the 'found' flag to 1, indicating at least one match was found.
                    }
                }
                if (found == 0) {
                    printf("Contact not found\n");
                    goto search1 ;// Go back and ask the user to enter a new name.
                }
            } else {
                printf("Please enter a valid name.\n");
            goto search1 ;// Go back and ask for the name again.
            }
            break;// Exit the case after processing.
        }
            goto search1 ;
// Case 2: Search by Phone Number
        case 2: 
search2:
            {
            printf("Enter phone number : ");
           // Input the phone number and store it temporarily in the last contact slot.
            scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].phone);
            // Step 3: Validate the phone number (function `create_phone` checks if the input is valid).
            
            val = create_phone(addressBook->contacts[addressBook->contactCount].phone);
            if (val == 1) {
                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strstr(addressBook->contacts[i].phone, addressBook->contacts[addressBook->contactCount].phone)) {
 // If a match is found, display the contact and store its index.
                        printf("%d. %s\t%s\t%s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        searchResults[searchCount++] = i; // Store the index of found contact
                        found = 1;// Indicate that a match was found.
                    }
                }
                if (found == 0) { // If no matches are found:
                    printf("Phone number not found\n");
                    goto search2 ;
                }
            } else {
                printf("Please enter a valid phone number.\n");
            }
            goto search2 ;// Go back and ask the user to enter a new phone number.
            break;
        }
      // Case 3: Search by Email
        case 3:
search3:
               {
            printf("Enter email id : ");
            scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].email);
            val = create_email(addressBook->contacts[addressBook->contactCount].email);
            if (val == 1)// If the email is valid:
            { //Loop through all contacts to find a match for the email.
                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strstr(addressBook->contacts[i].email,addressBook->contacts[addressBook->contactCount].email)) {
             // If a match is found, display the contact and store its index.

                        printf("%d. %s\t%s\t%s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        searchResults[searchCount++] = i; // Store the index of found contact
                        found = 1;// Indicate that a match was found.
                    }
                }
                if (found == 0) // If no matches are found
                {
                    printf("Email not found\n");
                    goto  search3;// Go back and ask the user to enter a new email.
                }
            } 
            else { // If the email is invalid:
                printf("Please enter a valid email.\n");
            }
            goto search3; 
            break; // Exit the case.
        }
      
        default://If the user enters an invalid option.
            printf("Invalid option\n");
            return;
    }

}





// Define the logic for Editcontact 
void editContact(AddressBook *addressBook)
{
    int option, valid;
    char new_value[30];

    // First, search for the contact to edit
    searchContact(addressBook);

    // Check if any contact was found
    if (searchCount > 0) {
        if (searchCount == 1) {
            // If only one result found, use that index
            index_i = searchResults[0];
        } else {
            // If multiple results found, let user select which contact to edit
            printf("Multiple contacts found. Please select one to edit:\n");
            for (int i = 0; i < searchCount; i++) {
                int idx = searchResults[i];
               // Display all found contacts
                printf("%d. Name: %s, Phone: %s, Email: %s\n", i + 1,
                       addressBook->contacts[idx].name,
                       addressBook->contacts[idx].phone,
                       addressBook->contacts[idx].email);
            }
           //user to select which contact to edit
            printf("Enter the number of the contact you want to edit: ");
            scanf("%d", &option);

            // Validate user selection
            if (option < 1 || option > searchCount) {
                printf("Invalid selection.\n");
                return;
            }
            // Get the index of the selected contact for editing
            index_i = searchResults[option - 1];
        }

         //user with options to edit Name, Phone, or Email
        printf("Choose an option to edit:\n 1.Name\n 2.Phone\n 3.Email\n");
        scanf("%d", &option);

        switch (option)
        {
            case 1:
                // Edit name
                printf("Enter new name: ");
                scanf(" %[^\n]", new_value); // Get the new name from the user

                valid = create_name(new_value);// Validate the new name
                if (valid) {
                    strcpy(addressBook->contacts[index_i].name, new_value);// Update the name
                    printf("Name updated successfully.\n");
                } else {
                    printf("Invalid name. Please try again.\n");
                }
                break;

            case 2:
                // Edit phone number
                printf("Enter new phone number: ");
                scanf(" %[^\n]", new_value);

                valid = create_phone(new_value);// Validate the new phone number
                if (valid) {
                    strcpy(addressBook->contacts[index_i].phone, new_value);
                    printf("Phone number updated successfully.\n");
                } else {
                    printf("Invalid phone number. Please try again.\n");
                }
                break;

            case 3:
                // Edit email
                printf("Enter new email: ");
                scanf(" %[^\n]", new_value);  // Get the new phone email

                valid = create_email(new_value); // Validate the new email id
                if (valid) {
                    strcpy(addressBook->contacts[index_i].email, new_value);// Update the gmail.id
                    printf("Email updated successfully.\n");
                } else {
                    printf("Invalid email. Please try again.\n");
                }
                break;

            default:
                printf("Invalid option.\n");
                break;
           }
    }
            else {
                // No contacts found display mesg
              printf("No contact found to edit.\n");
             }
}



// Define the logic for delete conatacts
void deleteContact(AddressBook *addressBook)
 {// Step 1: Search for contacts to delete
    searchContact(addressBook);  // Calls a function to search for contacts based on user input

 // Step 2: Check if multiple contacts were found
    if (searchCount > 1)
    {
        printf("\nMultiple contacts found. Please select one to delete:\n\n");
        for (int i = 0; i < searchCount; i++)
        {
            int index = searchResults[i];
           // Display all found contacts
            printf("%d. Name: %s, Phone: %s, Email: %s\n", i + 1,
                   addressBook->contacts[index].name,
                   addressBook->contacts[index].phone,
                   addressBook->contacts[index].email);
        }

        int option;
// Step 3: Prompt the user to select which contact to delete
        printf("Enter the number of the contact you want to delete: ");
        scanf("%d", &option);
 // Step 4: Validate the selection
        if (option < 1 || option > searchCount) 
        {
            printf("Invalid selection. No contact deleted.\n");
            return;
        }

        option--; // Adjust for zero-based index
// Step 5: Delete the selected contact by shifting the rest of the contacts up
        int indexToDelete = searchResults[option];

        for (int i = indexToDelete; i < addressBook->contactCount - 1; i++) {
            addressBook->contacts[i] = addressBook->contacts[i + 1];// Shift contacts up
        }
// Step 6: Reduce the contact count
        addressBook->contactCount--; 
        printf("Contact deleted successfully.\n");
    } 
        else {
           printf("No contact found to delete.\n");  // If no or only one contact found, show a message
         }
}


