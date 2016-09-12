/******************************************************************************
* Test program for the Implementation of a hash table as required for 
* COMP 272 assignment 2 question 4.
*
* Author: Robert Ryan Dunn
* SN: 3070207
* Date: 9 September, 2016
******************************************************************************/

#include "HashTable.h"
#include <iostream>

using std::cout;
using std::endl;

int hashEntries[] = {1,5,21,26,39,14,15,16,17,18,19,20,111,145,146};


void findEntry(HashTable<int> &HT, int x)			//remove entry
{
	try
	{
		HashItem<int>* HI = HT.find(x);				//find key if possible
		cout << "The entry " << HI->entry << 
			" has been found." << endl << endl;
	}
	catch (NonexistentEntry& err)					//show error if not
	{
		cout << "Exception: " << err.getMessage()
			<< endl << endl;						
	}
}

void removeEntry(HashTable<int> &HT, int x)			//remove entry
{
	try
	{
		HT.remove(x);								//remove key if possible
	}
	catch (NonexistentEntry& err)					//show error if not
	{
		cout << "Exception: " << err.getMessage()
			<< endl << endl;						
	}
}

void sizeHash(HashTable<int>& HT)					//show the hash table size
{
	cout << "The current size of the HashMap is: "
		<< HT.size() << endl << endl;
}

void addEntry(HashTable<int> &HT, int x)			//add entry
{
	try
	{
		HT.add(x);									//add entry if possible
	}
	catch (EntryExists& err )						//show error if not
	{
		cout << "Exception: " << err.getMessage()
			<< endl << endl;		
	}
}

void testCase(int &test)							//prints test case value
{
	cout << "Test Case: " << test
		<< endl;
	test++;
}

int main(void)
{
	HashTable<int> HT(5);							//create hash table
	int test = 1;									//assign test case value

	testCase(test);									//print out test case no.
	sizeHash(HT);									//hash table size

	testCase(test);									//print out test case no.
	for (int i : hashEntries)
		addEntry(HT,i);								//add items to hash table
	sizeHash(HT);									//hash table size
	
	testCase(test);									//print out test case no.
	for (int i : hashEntries)
		findEntry(HT,i);							//find entries in hash table
		
	testCase(test);									//print out test case no.
	for (int i = 14; i < 22; i++)
		removeEntry(HT,i);							//remove entries 14-21
	sizeHash(HT);									//hash table size
	
	testCase(test);									//print out test case no.
	addEntry(HT,5);									//add a duplicate
	findEntry(HT,16);								//find a nonexistent entry
	removeEntry(HT,16);								//remove a nonexistent entry
	
	testCase(test);									//print out test case no.
	for (int i = 14; i < 22; i++)
		addEntry(HT,i);								//add entries 14-21
	sizeHash(HT);									//hash table size
	
	testCase(test);									//print out test case no.
	for (int i : hashEntries)
		findEntry(HT,i);							//find entries in hash table
		
	testCase(test);									//print out test case no.
	for (int i : hashEntries)
		removeEntry(HT,i);							//remove items to hash table
	sizeHash(HT);									//hash table size		

	testCase(test);									//print out test case no.
	for (int i : hashEntries)
		addEntry(HT,i);								//add items to hash table
	sizeHash(HT);									//hash table size

	return EXIT_SUCCESS;							//exit success
}