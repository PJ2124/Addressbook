#ifndef FILE_H
#define FILE_H
#include "contact.h"

void saveContactsToFile(AddressBook *addressBook);
int file_open(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);

#endif
