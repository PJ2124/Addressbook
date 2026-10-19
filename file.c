
#include <stdio.h>
#include "contact.h"
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
//    printf("im her inside save\n");
    FILE *fptr_temp;

     fptr_temp =fopen("temp.csv","w" );

    if (fptr_temp == NULL )
    {
        perror("fopen ");
        printf("Error one temp file \n ");
        return  ;
        
    }
    
     
    fprintf(fptr_temp, "%d\n",addressBook->contactCount ); // print number 
      for (int i=0; i <addressBook->contactCount;i++)  
      {
    
          fprintf(fptr_temp, "%s,%s,%s\n",
                  addressBook->contacts[i].name,
                  addressBook->contacts[i].phone,
                  addressBook->contacts[i].email);
          

      }

      remove("add.csv");
      rename("temp.csv", "PJCon.csv");

     printf("Contacts save successfully.\n");

}

int file_open(AddressBook *addressBook)
{
   addressBook->fptr_file = fopen("PJCon.csv","r");
  
      if(addressBook->fptr_file == NULL )
      {
          perror("fopen ");
          printf("Error File not open\n");
          return 0;
      }
}


void loadContactsFromFile(AddressBook *addressBook)
{
    
     
   // printf("inside the load in file\n");
  
    fscanf(addressBook -> fptr_file, "%d", &addressBook->contactCount );  

    for (int i=0 ; i<addressBook->contactCount ;i++ )
    {
        fscanf(addressBook -> fptr_file, " %[^,], %[^,], %[^\n]",
              addressBook->contacts[i].name ,
              addressBook->contacts[i].phone ,
              addressBook->contacts[i].email) ; 
              
    }

    printf("Contact loaded successfull.\n");

}
