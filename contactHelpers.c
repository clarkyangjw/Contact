/* -------------------------------------------
Name:Jiawei Yang
Student number:121134183
Date:Nov.17 2018
----------------------------------------------
Assignment: 2
Milestone:  4
---------------------------------------------- */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// This source file needs to "know about" the SYSTEM string library functions.
// HINT: The library name is string.h.
//       #include the string.h header file on the next line:
#include <string.h>

// ----------------------------------------------------------
// Include your contactHelpers header file on the next line:
#include "contactHelpers.h"


// ----------------------------------------------------------
// define MAXCONTACTS for sizing contacts array (5):
#define MAXCONTACTS 5


//------------------------------------------------------
// Function Definitions
//------------------------------------------------------

// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        function definitions below...            |
// +-------------------------------------------------+

// clearKeyboard
void clearKeyboard(void)
{
	while (getchar() != '\n')
		continue; // empty execution code block on purpose
}

// pause:
void pause(void)
{
	printf("(Press Enter to Continue)");
	clearKeyboard();
}

// getInt:
int getInt(void)
{
	int value;
	char NL = 'x';
	while (NL != '\n')
	{
		scanf("%d%c", &value, &NL);
		if (NL != '\n') {
			clearKeyboard();
			printf("*** INVALID INTEGER *** "
				"<Please enter an integer>: ");
		}
	}
	return value;
}

// getIntInRange:
int getIntInRange(int min, int max)
{
	int value, keeptrying = 1;
	do
	{
		value = getInt();
		if (value < min || value > max)
		{
			printf("*** OUT OF RANGE *** "
				"<Enter a number between %d and %d>: ", min, max);
		}
		else
		{
			keeptrying = 0;
		}
	} while (keeptrying);
	return value;
}

// yes:
int yes(void)
{
	char firstChar, secondChar;
	int value = -1, keeptrying = 1;
	do
	{
		scanf("%c%c", &firstChar, &secondChar);
		if (secondChar != '\n')
		{
			clearKeyboard();
			printf("*** INVALID ENTRY *** "
				"<Only (Y)es or (N)o are acceptable>: ");
		}
		else
		{
			if (firstChar == 'Y' || firstChar == 'y')
			{
				value = 1;
				keeptrying = 0;
			}
			else if (firstChar == 'N' || firstChar == 'n')
			{
				value = 0;
				keeptrying = 0;
			}
			else
			{
				printf("*** INVALID ENTRY *** "
					"<Only (Y)es or (N)o are acceptable>: ");
			}
		}
	} while (keeptrying);
	return value;
}

// menu:
int menu(void)
{
	int value;
	printf("Contact Management System\n"
		"-------------------------\n"
		"1. Display contacts\n"
		"2. Add a contact\n"
		"3. Update a contact\n"
		"4. Delete a contact\n"
		"5. Search contacts by cell phone number\n"
		"6. Sort contacts by cell phone number\n"
		"0. Exit\n\n"
		"Select an option:> ");
	value = getIntInRange(0, 6);
	return value;
}

// contactManagerSystem:
void contactManagerSystem(void)
{
	struct Contact contact[MAXCONTACTS] = {
		{
		{ "Rick", {'\0'}, "Grimes"},
		{ 11, "Trailer Park", 0, "A7A 2J2", "King City" },
		{ "4161112222", "4162223333", "4163334444" }},
		{
		{ "Maggie", "R.", "Greene" },
		{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
		{ "9051112222", "9052223333", "9053334444" }},
		{
		{ "Morgan", "A.", "Jones" },
		{ 77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough" },
		{ "7051112222", "7052223333", "7053334444" }},
		{
		{ "Sasha", {'\0'}, "Williams" },
		{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
		{ "9052223333", "9052223333", "9054445555" }},
	};
	int value, keeptyring = 1;
	do
	{
		value = menu();
		if (value == 0)
		{
			printf("\nExit the program? (Y)es/(N)o: ");
			if (yes())
			{
				printf("\nContact Management System: terminated\n");
				break;
			}
			else
			{
				printf("\n");
				continue;
			}
		}
		switch (value)
		{
		case 1: printf("\n"); displayContacts(contact, MAXCONTACTS); break;
		case 2: printf("\n"); addContact(contact, MAXCONTACTS); break;
		case 3: printf("\n"); updateContact(contact, MAXCONTACTS); break;
		case 4: printf("\n"); deleteContact(contact, MAXCONTACTS); break;
		case 5: printf("\n"); searchContacts(contact, MAXCONTACTS); break;
		case 6: printf("\n"); sortContacts(contact, MAXCONTACTS); break;
		}
		pause();
		printf("\n");
	} while (keeptyring);
}

// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        empty function definitions below...      |
// +-------------------------------------------------+

// getTenDigitPhone:
void getTenDigitPhone(char telNum[])
{
	int keeptrying = 1;
	int i;
	do {
		scanf("%10[^\n]", telNum);
		clearKeyboard();
		if (strlen(telNum) != (SIZEOFNUMBERS - 1))
		{
			printf("Enter a 10-digit phone number: ");
		}
		else
		{
			for (i = 0; telNum[i] != '\0'; i++)
			{
				if (telNum[i] < '0' || telNum[i] > '9')
				{
					printf("Enter a 10-digit phone number: ");
					break;
				}
			}
			if (telNum[i] == '\0')
			{
				keeptrying = 0;
			}
		}
	} while (keeptrying);
}

// findContactIndex:
int findContactIndex(const struct Contact contact[], int sizeOfConArr, const char enteredNum[])
{
	int index;
	for (index = 0; index < sizeOfConArr; index++)
	{
		if (strcmp(contact[index].numbers.cell, enteredNum) == 0)
		{
			break;
		}
	}
	if (index == sizeOfConArr)
	{
		index = -1;
	}
	return index;
}

// displayContactHeader:
void displayContactHeader(void)
{
	printf("+-----------------------------------------------------------------------------+\n"
		"|                              Contacts Listing                               |\n"
		"+-----------------------------------------------------------------------------+\n");
}

// displayContactFooter:
void displayContactFooter(int totalContacts)
{
	printf("+-----------------------------------------------------------------------------+\n"
		"Total contacts: %d\n\n", totalContacts);
}

// displayContact:
void displayContact(const struct Contact*contact)
{
	printf(" %s ", contact->name.firstName);

	if (contact->name.middleInitial[0] != '\0')
	{
		printf("%s ", contact->name.middleInitial);
	}
	printf("%s\n", contact->name.lastName);

	printf("    C: %-10s   H: %-10s   B: %-10s\n", contact->numbers.cell, contact->numbers.home, contact->numbers.business);

	printf("       %d %s, ", contact->address.streetNumber, contact->address.street);
	if (contact->address.apartmentNumber != 0)
	{
		printf("Apt# %d, ", contact->address.apartmentNumber);
	}
	printf("%s, %s\n", contact->address.city, contact->address.postalCode);
}

// displayContacts:
void displayContacts(const struct Contact contact[], int sizeOfConArr)
{
	int i, totalContacts = 0;
	displayContactHeader();
	for (i = 0; i < sizeOfConArr; i++)
	{
		if (strlen(contact[i].numbers.cell) > 0)
		{
			displayContact(&contact[i]);
			totalContacts++;
		}
	}
	displayContactFooter(totalContacts);
}

// searchContacts:
void searchContacts(const struct Contact contact[], int sizeOfConArr)
{
	char entered[SIZEOFNUMBERS];
	int index;
	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(entered);
	index = findContactIndex(contact, sizeOfConArr, entered);
	if (index >= 0 && index < sizeOfConArr)
	{
		printf("\n");
		displayContact(&contact[index]);
		printf("\n");
	}
	else
	{
		printf("*** Contact NOT FOUND ***\n\n");
	}
}

// addContact:
void addContact(struct Contact contact[], int sizeOfConArr)
{
	int i;
	for (i = 0; i < sizeOfConArr; i++)
	{
		if (strlen(contact[i].numbers.cell) == 0)
		{
			getContact(&contact[i]);
			printf("--- New contact added! ---\n\n");
			break;
		}
	}
	if (i == sizeOfConArr)
	{
		printf("*** ERROR: The contact list is full! ***\n\n");
	}
}

// updateContact:
void updateContact(struct Contact contact[], int sizeOfConArr)
{
	char entered[SIZEOFNUMBERS];
	int index;
	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(entered);
	index = findContactIndex(contact, sizeOfConArr, entered);
	if (index >= 0)
	{
		printf("\nContact found:\n");
		displayContact(&contact[index]);
		printf("\nDo you want to update the name? (y or n): ");
		if (yes())
		{
			getName(&contact[index].name);
		}
		printf("Do you want to update the address? (y or n): ");
		if (yes())
		{
			getAddress(&contact[index].address);
		}
		printf("Do you want to update the numbers? (y or n): ");
		if (yes())
		{
			getNumbers(&contact[index].numbers);
		}
		printf("--- Contact Updated! ---\n\n");
	}
	else
	{
		printf("*** Contact NOT FOUND ***\n\n");
	}
}

// deleteContact:
void deleteContact(struct Contact contact[], int sizeOfConArr)
{
	char entered[SIZEOFNUMBERS];
	int index;
	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(entered);
	index = findContactIndex(contact, sizeOfConArr, entered);
	if (index >= 0)
	{
		printf("\nContact found:\n");
		displayContact(&contact[index]);
		printf("\nCONFIRM: Delete this contact? (y or n): ");
		if (yes())
		{
			contact[index].numbers.cell[0] = '\0';
			printf("--- Contact deleted! ---\n");
		}
	}
	else
	{
		printf("*** Contact NOT FOUND ***\n");
	}
	printf("\n");
}

// sortContacts:
void sortContacts(struct Contact contact[], int sizeOfConArr)
{
	int i, j, m;
	struct Contact temp;
	for (i = 0; i < sizeOfConArr; i++)
	{
		m = i;
		for (j = i + 1; j < sizeOfConArr; j++)
		{
			if (strcmp(contact[j].numbers.cell, contact[m].numbers.cell) < 0)
			{
				m = j;
			}
		}
		if (m != i)
		{
			temp = contact[i];
			contact[i] = contact[m];
			contact[m] = temp;
		}
	}
	printf("--- Contacts sorted! ---\n\n");
}