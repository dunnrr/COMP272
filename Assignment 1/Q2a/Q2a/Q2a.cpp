/******************************************************************************
* Test file for question 2a for Assignment 1 of COMP 272
* This program is designed to run tests as per stated in Assignment 1 
* submission
*
* Author:	Robert Ryan Dunn
* Stu. No.:	3070207
* Date:		5 June, 2016
******************************************************************************/

#include <iostream>
#include "SLinkedList.h"

void printList(SLinkedList<int> &list)
// This function outputs what the current list is
{
	std::cout << "The current list is: ";
	list.print();							// retrieve list
	std::cout << std::endl << std::endl;
}

void addList(SLinkedList<int> &list, int size)
// This function adds a given number of items to the list 
{
	printList(list);						// print the current list
	for (int i = 0; i < size; i++)			// cycle adding to list
	{
		list.addFront(i);					// add an item to list
		printList(list);					// print the current list
	}
}

void printTest(int testCase)
// This function prints out which test case we're running
{
	std::cout << "Test Case " << testCase << ":" << std::endl;
}

int main()
// The main function will run through the test cases as outlined in the 
// attached assignment documentation
{
	SLinkedList<int> list;					// initialize the list
	int size = 5;							// initialize a size
	int testCase = 1;						// initialize test cases
	
	std::cout << "Creating initial list... "
		<< std::endl << std::endl;			// create the list
	addList(list,size);

	for (int i = -1; i <= size; i++)		// run through first 6 test cases
	{
		printTest(testCase);				// inform us of which test case
		testCase++;							// increment test case
		list.swap(i);						// attempt to swap items
		printList(list);					// print the current list
	}
	
	std::cout << "Emptying list... " 
		<< std::endl << std::endl;			// delete the contents of the list
	while (!list.empty())					// check for an empty list
		{
			list.removeFront();				// remove front item from list
			printList(list);				// print out current list
		}

	int i = 1;								// initialize counter
	while (i <= 2)							// run final two test cases
	{
		printTest(testCase);				// inform us of which test case
		testCase++;							// increment test case
		list.swap(0);						// try to swap the lead element
		printList(list);					// print the current list
		list.addFront(i);					// add an item to the list
		i++;								// increment counter
	}

	return EXIT_SUCCESS;					// exit successfully
}
