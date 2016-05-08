// Q1b.cpp : Defines the entry point for the console application.
//


#include "Stack.h"
#include <iostream>


int main()
{
	Stack<int> testStack;
	std::cout << "The integers as they are being pushed into the stack:" 
		<< std::endl;
	for (int i = 0; i <= 10; i++)
	{
		testStack.push(i);
		std::cout << testStack.top() << " ";
	}
	std::cout << std::endl << std::endl;
	std::cout << "The integers coming back off the top of the stack:"
		<< std::endl;
	for (int i = 0; i <= 10; i++)
	{
		std::cout << testStack.top() << " ";
		testStack.pop();
	}
	std::cout << std::endl << std::endl;
    return EXIT_SUCCESS;
}

