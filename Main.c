///////////////////////////////////////////////
//
// CPE 2073
// Homework 11
//
// Hien Do, soz131
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>	// for qsort() and bsearch()
#include <string.h> // for strcmp()

typedef struct
{
	char firstname[16];
	char lastname[16];
	char address[32];
	char city[24];
	char county[24];
	char state[3];
	char zip[9];
	char phone[16];
	char email[36];
} Student;

int nameCmp(Student* s1, Student* s2)
{
	int name = strcmp(s1->lastname, s2->lastname); 
	if (name == 0) // if the first and last names are identical, two records are equal
		return strcmp(s1->firstname, s2->firstname); // return record
	return name; // else return positive and negative
}

void sortRecords(Student data[], int count)
{
	printf("\nBefore sorting\n");
	for (int i = 0; i < 10; i++) 
		printf("%s %s\n", data[i].firstname, data[i].lastname); // print a list of 10 records first name and last name 

	qsort(data, count, sizeof(Student), nameCmp); // sort the data set

	printf("\nAfter sorting:\n");
	for (int i = 0; i < 10; i++)
		printf("%s %s\n", data[i].firstname, data[i].lastname); // print a list of 10 records firstname and lastname after sorting

	return 0;
}

void findRecord(Student* find, Student data[], int count)
{

	Student* result = bsearch(find, data, count, sizeof(Student), nameCmp); //searching a sorted array 
	

	if (result != 0) 
	{
		//if the record exact print out phone and lastname and firstname
		printf("Found: %s %s %s\n", result->firstname, result->lastname, result->phone);
	}
	else 
	{// else if the record not found print Bob Applonie
		printf("Record not found: Bob Applonie\n");
	}
}

// Function to read one row from the given file and populate a Student structure
int readRowFromFile(FILE* f, Student* s)
{
	memset(s, 0, sizeof(Student));
	return fscanf(f, " %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %s\n",
		s->firstname, s->lastname, s->address, s->city, s->county, s->state, s->zip, s->phone, s->email);
}

// Declare an array variable to hold all the records
Student rData[1000];

// Main routine
int main()
{
	// Variable to hold the print format string
	char* fmt = "%-12s%-16s%-32s%-20s%-3s%-6s%-24s\n";

	// Open the file for reading, MAKE SURE THE FILE NAME MATCHES WHAT YOU HAVE
	FILE* f = fopen("Samplerecords", "rt");
	if (!f)
	{
		printf("Unable to open file. \n");
		return 0;
	}

	// Variable to hold the number of records actually read
	int count = 0;

	// Skip the header row
	int rc = readRowFromFile(f, &rData[0]);

	// Read the rest of the file
	while (!feof(f) && count < 1000)
	{
		rc = readRowFromFile(f, &rData[count]);
		if (rc > 0)
			count++;
	}

	// Close the file
	fclose(f);

	// Sort the list
	sortRecords(rData, count);

	// Find the record of "Bernardo Figeroa"
	Student find = { "Bernardo", "Figeroa" };
	findRecord(&find, rData, count);

	// Look for a record that is not in the list
	Student notInList = { "Bob", "Applonie" };
	findRecord(&notInList, rData, count);

	return 0;
}