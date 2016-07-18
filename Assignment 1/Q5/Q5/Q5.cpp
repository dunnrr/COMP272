/******************************************************************************
* Test file for question 5 for Assignment 1 of COMP 272
* This program is designed to run tests as per stated in Assignment 1
* submission
*
* Author:	Robert Ryan Dunn
* Stu. No.:	3070207
* Date:		17 July, 2016
******************************************************************************/

#include <iostream>
#include "DLinkedList.h"

void createList(DLinkedList<int> &list)
//This function is used to create a list
{
	for (int i = 0; i < 5; i++)
	{
		list.addFront(i);						// add items to list
	}
}

void printList(DLinkedList<int> &list)
//this function is used to output the contents of the
//list
{
	std::cout << "The list values are: " << std::endl;
	list.print();										
	std::cout << std::endl << std::endl;
}

void printTest(int testCase)
// This function prints out which test case we're running
{
	std::cout << "Test Case " << testCase << ":" << std::endl;
}

int main()
//test function
{
	DLinkedList<int> list;						// initialize the list
	int testCase = 1;							// initialize test case
	
	printTest(testCase);						// inform us of which test case
	testCase++;									// increment test case
	printList(list);							// print out current list
	list.reverse();								// reverse the list
	printList(list);							// print out current list

	printTest(testCase);						// inform us of which test case
	testCase++;									// increment test case
	createList(list);							// create input list		
	printList(list);							// print out current list
	list.reverse();								// reverse the list
	printList(list);							// print out current list
	return EXIT_SUCCESS;						// exit success
}