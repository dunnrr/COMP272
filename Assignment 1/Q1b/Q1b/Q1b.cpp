/******************************************************************************
* Test program for the Implementation of push() and pop(X) functions for a
* stack using two queues as per COMP 272 assignment 1b.
*
* Author: Robert Ryan Dunn
* SN: 3070207
* Date: 5 June, 2016
******************************************************************************/

#include "Stack.h"
#include <iostream>

void printTest(int &testCase)							//print test case value
{
	std::cout << "Test Case " << testCase << ":"
		<< std::endl;
	testCase++;
}

void print(Stack<int> &testStack)						//print current stack
{
	std::cout << "The stack is currently: ";		
	testStack.print();
	std::cout << std::endl << std::endl;
}

void top(Stack<int> &testStack)							//print value of top
{
	try
	{
		std::cout << "The top value is: " 
			<< testStack.top() 
			<< std::endl << std::endl;					//print top value
	}
	catch (StackEmpty& err)
	{
		std::cout << "Exception: " << err.getMessage()
			<< std::endl << std::endl;					//print error message
	}
}

void pop(Stack<int> &testStack)
{
	try
	{
		testStack.pop();								//pop stack
	}
	catch (StackEmpty& err)
	{
		std::cout << "Exception: " << err.getMessage()
			<< std::endl << std::endl;					//print error message
	}
}

int main()
{
	int testCase = 1;									//test case counter
	int size = 5;										//number of push items
	Stack<int> testStack;								//test Stack
	
	print(testStack);									//print current stack

	printTest(testCase);								//print out test case no.
	for (int i = 0; i <= size; i++)						//cycle adding to stack
	{
		testStack.push(i);								//push onto stack
		print(testStack);								//print current stack
	}

	printTest(testCase);								//print out test case no.
	top(testStack);										//retreive top of stack
	print(testStack);									//print current stack

	printTest(testCase);								//print out test case no.
	while (!testStack.empty())							//cycle until empty
	{
		pop(testStack);									//pop stack
		print(testStack);								//print current stack
	}

	printTest(testCase);								//print out test case no.
	top(testStack);										//retreive top of stack
	print(testStack);									//print current stack

	printTest(testCase);								//print out test case no.
	pop(testStack);										//pop stack
	print(testStack);									//print current stack
	
	return EXIT_SUCCESS;								//exit success
}

