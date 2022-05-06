/*
Name: Autumn Boone
3/25/2022
Lab #8
CSE 130 Section 1A with Dr. Yampolskiy
Description: phonebook that you can access stored memory through files
*/

//C libraries - includes access to the malloc and realloc functions
#include <stdio.h>
#include <stdlib.h>

// structure that accounts for the phonebook "data type"
typedef struct {
	char first[100];
	char last[100];
	char phone[100];
} phoneBook;

// global count variable
int count = 0;

// initializing arrayofContacts globally
phoneBook *arrayofContacts;

// add a friend function
void addfriend()
{
	count++;
	arrayofContacts = realloc(arrayofContacts, count*sizeof(phoneBook));
	
	printf("First name: \n");
	scanf("%s", arrayofContacts[count-1].first);
	printf("Last name: \n");
	scanf("%s", arrayofContacts[count-1].last);
	printf("Phone number: \n");
	scanf("%s", arrayofContacts[count-1].phone);
	
	printf("Contact added to the phone book\n\n");
}

// delete a friend function
void deletefriend()
{	
	int contactNumber, contactElement;
	char delfriend[100];
	printf("Which friend would you like to delete?\nPlease print their first name.\n");
	scanf("%s", delfriend);
	for (contactNumber = 0; contactNumber < count; contactNumber++)
	{
		if (strcmp(delfriend, arrayofContacts[contactNumber].first) == 0)
		{
			for (contactElement = contactNumber; contactElement < count-1; contactElement++)
			{
				arrayofContacts[contactElement] = arrayofContacts[contactElement + 1];
			}
		break;
		}
	}
	count--;
	arrayofContacts = realloc(arrayofContacts, count*sizeof(phoneBook));
	printf("Contact deleted from the phone book\n\n");
}

// see all contacts in phonebook function
char seephonebook()
{
	int i;
	printf("\nPhone Book Entries:\n");
		for (i=0; i <= count-1; i++)
		{
			printf("%i ) %s %s %s \n", (i+1), arrayofContacts[i].first, arrayofContacts[i].last, arrayofContacts[i].phone);
		}
	printf("\n");
}

// alphabetize function
void alphabetize()
{
	char tmp[100];
	int i, j;
	
	// grabs first contact's first name
	for (i = 0; i < count-1; i++)
	{
		// compares first name to itself then every consequent first name
		for (j=i+1; j < count; j++)
		{
			if (strcmp(arrayofContacts[i].first, arrayofContacts[j].first) > 0)
			{
				strcpy(tmp, arrayofContacts[i].first);
				strcpy(arrayofContacts[i].first, arrayofContacts[j].first);
				strcpy(arrayofContacts[j].first, tmp);
				//
				strcpy(tmp, arrayofContacts[i].last);
				strcpy(arrayofContacts[i].last, arrayofContacts[j].last);
				strcpy(arrayofContacts[j].last, tmp);
				//
				strcpy(tmp, arrayofContacts[i].phone);
				strcpy(arrayofContacts[i].phone, arrayofContacts[j].phone);
				strcpy(arrayofContacts[j].phone, tmp);
			}
		}
	}
	
	printf("\nAlphabetized list: \n");
	for (i = 0; i < count; i++)
	{
		printf("%i ) %s %s %s \n", (i+1), arrayofContacts[i].first, arrayofContacts[i].last, arrayofContacts[i].phone);
	}
	printf("\n");
}

// find a specific friend function
char findFriend()
{
	int contactNumber;
	int i;
	char afriend[100];
	printf("Which friend would you like to find?\nPlease print their first name.\n");
	scanf("%s", afriend);
	for (contactNumber = 0; contactNumber < count; contactNumber++)
	{
		if (strcmp(afriend, arrayofContacts[contactNumber].first) == 0)
		{
			printf("\n%s's Contact Information: \nFirst name: %s \nLast name: %s \nPhone number: %s \n\n", arrayofContacts[contactNumber].first, arrayofContacts[contactNumber].first, arrayofContacts[contactNumber].last, arrayofContacts[contactNumber].phone);
		}
	}
}


// get a random friend function
char randomize()
{
	srand(time(0));
	int randChoice = rand() % count;
	printf("\nRandomly selected contact information: \nFirst name: %s \nLast name: %s \nPhone number: %s \n\n", arrayofContacts[randChoice].first, arrayofContacts[randChoice].last, arrayofContacts[randChoice].phone);	
}

// delete all the friends function
void deleteAll()
{
	int contactNumber, contactElement;
	for (contactNumber = 0; contactNumber <= count; contactNumber++)
	{
		for (contactElement = 0; contactElement <= count-1; contactElement++)
		{
			arrayofContacts[contactElement] = arrayofContacts[contactElement + 1];
		}
	break;
	}
	count = count - count;
	// to test if program deleted all contacts represented in count - printf("%d", count);
	// no realloc..?
	// arrayofContacts = realloc(arrayofContacts, count*sizeof(phoneBook));
	printf("\nALL contacts have been deleted from your phone book\n\n");
}

//main function
int main()
{	
	// initializing choice variable
	int choice;
	
	// choosing file name
	char fileName[100] = "phonebook.txt";
	printf("What do you want your file name to be called?");
	scanf("%s", fileName);
	
	// creating file
	FILE* phoneFILE = fopen(fileName, "r");
	fscanf(phoneFILE, "%d", &count);
	arrayofContacts = malloc(count*sizeof(phoneBook));	
	int i;
	for (i=0; i <= count-1; i++)
	{
		fscanf(phoneFILE, "%s %s %s\n", arrayofContacts[i].first, arrayofContacts[i].last, arrayofContacts[i].phone);
	}
	fclose(phoneFILE);
		
	do
	{	
		// prints main menu for the phonebook
		printf("\nPhone Book Application\t\n");
		printf("(1) Add friend\n");
		printf("(2) Delete friend\n");
		printf("(3) Show phone book\n");
		printf("(4) Alphabetize phone book\n");
		printf("(5) Find phone number from first name\n");
		printf("(6) Randomly select contact\n");
		printf("(7) Delete everyone from phonebook\n");
		printf("(8) Save and exit phonebook\n");
		printf("What do you want to do: \n");
		scanf("%i", &choice);
		
		// allows user to add a friend
		if (choice == 1)
		{
			addfriend(arrayofContacts);
		}
		
		// allows user to delete a friend
		if (choice == 2)
		{
			deletefriend(arrayofContacts);
		}
		
		// allows user to see phonebook
		if (choice == 3)
		{
			seephonebook(arrayofContacts);
		}
		
		// alphabetize the phonebook
		if (choice == 4)
		{
			alphabetize(arrayofContacts);
		}
		
		// find a specific phone number when user enters their first name
		if (choice == 5)
		{
			findFriend(arrayofContacts);
		}
		
		// print a random contact
		if (choice == 6)
		{
			randomize(arrayofContacts);
		}
		
		// delete EVERYONE from the phonebook
		if (choice == 7)
		{
			deleteAll(arrayofContacts);
		}
				
	} while (choice != 8); // exits loop when user chooses option 8 (exit phonebook)
	
	// tells the user they have exited the phonebook
	if (choice == 8)
	{		
		// adding arrayofContacts to file
		FILE* phoneFILE = fopen(fileName, "w");
		
		if (phoneFILE == NULL)
			printf("\n Cannot open one of the files");
		else
		{
			fprintf(phoneFILE, "%d\n", count);
			for (i=0; i<=count-1; i++)
			{
				fprintf(phoneFILE, "%s %s %s\n", arrayofContacts[i].first, arrayofContacts[i].last, arrayofContacts[i].phone);
			}
			printf("Here is your saved phonebook: \n");
			for (i=0; i<=count-1; i++)
			{
				printf("%s %s %s\n", arrayofContacts[i].first, arrayofContacts[i].last, arrayofContacts[i].phone);
			}
			printf("Goodbye!");
		}
		fclose(phoneFILE);
	}
	
	//frees memory
	free(arrayofContacts);
	
	// informs programmer that the program has ran successfully
	return 0;	
}
